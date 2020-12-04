#include <iostream>               // подключаем заголовочный файл iostream
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <math.h>
#include <string>
#include <cstring>

constexpr uint16_t maxRamSize = 2;            // Max size of chunk in external sorting (MegaBytes).
constexpr uint8_t charBufferSize = 4;         // Buffer size to read data from given file (char = 1 byte).
constexpr float perfomanceCoefficient = 0.9 ; // Persentage of full RAM size use.
constexpr uint32_t chunkSizeLimit = (pow(1024,2) * maxRamSize / charBufferSize) * perfomanceCoefficient;

template <typename T>
void showChunk(const T &chunk) noexcept {
  for (const auto &element:chunk) {
    std::cout << element << std::endl;
  }
}

template <typename T>
void writeChunkToFile(const T &chunk, const std::string chucnkFileName) noexcept {
  std::ofstream chunkFile(chucnkFileName);
  for (const auto &element:chunk) {
    chunkFile << element;
  }
  chunkFile.close();
}

void readDataFromFile(const std::string &fileName) noexcept {
  char charBuffer[charBufferSize + 1];    // Buffer for readed data.
  std::vector<std::string> sortedChunk; // Sorted chunk of data from given file.
  std::ifstream originFile(fileName);     // Open given file to read data.
  auto chunkFileIndex = 0;
  if (originFile) { // Check that given file is exist and successfully opened.
    std::cout << "[FileSorter] - Reading data from " << fileName << " - [START]" << std::endl;
    while (!originFile.eof()) {
      originFile.read(charBuffer, charBufferSize);
      // sortedChunk.insert(charBuffer);
      sortedChunk.push_back(charBuffer);
      if (sortedChunk.size() >= chunkSizeLimit) {
        writeChunkToFile(sortedChunk, std::to_string(chunkFileIndex));
        sortedChunk.erase(sortedChunk.begin(), sortedChunk.end());
        ++chunkFileIndex;
        std::cout << "[FileSorter] - Create chunk # " << chunkFileIndex << ". Size - " <<
                                 chunkSizeLimit * charBufferSize / pow(1024,2) << "Mb" << std::endl;
        std::cout << originFile.tellg() << std::endl;
        continue;
      }
    }
  } else {
    std::cerr << "Can't open file " << fileName << std::endl;
  }
  writeChunkToFile(sortedChunk, std::to_string(chunkFileIndex));
  originFile.close();
  std::cout << "[FileSorter] - Reading data from " << fileName << " - [FINISHED]" << std::endl;
}

int main() {
  std::cout << "[FileSorter] - Chunk size limit is " << chunkSizeLimit << std::endl;
  readDataFromFile("test-data/TestDataFile");
}
