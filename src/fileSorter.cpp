#include <iostream>
#include <fstream>
#include <memory>
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
inline void showChunk(const T &chunk) noexcept {
  for (const auto &element:chunk) {
    std::cout << element << std::endl;
  }
}

template <typename T>
inline void writeChunkToFile(const T &chunk, const std::string chunkFileName) noexcept {
  std::cout << "[FileSorter] - Create chunk # " << chunkFileName << ". Size - " <<
                            chunk.size() * charBufferSize / pow(1024,2) << " Mb" << std::endl;
  std::ofstream chunkFile(chunkFileName);
  for (const auto &element:chunk) {
    chunkFile << element;
  }
  chunkFile.close();
}

// Split data from given file to sorted chunks (files).
std::vector<std::string> splitFileToChunks(const std::string &fileName) noexcept {
  std::string currentChunkName;
  std::vector<std::string> chunksNameList;
  char charBuffer[charBufferSize + 1];    // Buffer for readed data.
  std::multiset<std::string> sortedChunk; // Sorted chunk of data from given file.
  std::ifstream originFile(fileName);     // Open given file to read data.
  std::cout << "[FileSorter] - Splitting data from " << fileName << " to chunks - [START]" << std::endl;
  auto currentChunkIndex = 0;             // Index of current chunk.
  if (originFile) {                       // Check that given file is exist and successfully opened.
    while (!originFile.eof()) {
      originFile.read(charBuffer, charBufferSize);                 // Read data from file with unsorted data.
      sortedChunk.insert(charBuffer);                              // Add data to sorted container.
      if (sortedChunk.size() >= chunkSizeLimit) {                  // Check sorted container size.
        currentChunkName = std::to_string(currentChunkIndex);
        chunksNameList.push_back(currentChunkName);                // Store name of current chunk.
        writeChunkToFile(sortedChunk, currentChunkName);           // Output sorted chunk to external file.
        sortedChunk.erase(sortedChunk.begin(), sortedChunk.end()); // Clear sorted chunk to repeat process.
        ++currentChunkIndex;
      }
    }
  } else {
    std::cerr << "[FileSorter] - Can't open file " << fileName << std::endl;
  }
  currentChunkName = std::to_string(currentChunkIndex);
  chunksNameList.push_back(currentChunkName);
  writeChunkToFile(sortedChunk, currentChunkName);
  originFile.close();
  std::cout << "[FileSorter] - Splitting data to chunks - [FINISHED]" << std::endl;
  return chunksNameList;
}

// void mergeSortFromChunks(const std::vector<std::string> *chunksList, const std::string &sortedFileName) noexcept {
void mergeSortFromChunks(const std::vector<std::string> *chunksList, const std::string &sortedFileName) noexcept {
  std::cout << "[FileSorter] - Merge sort from " << chunksList->size() << " chunks - [START]" << std::endl;
  std::cout << "[FileSorter] - Merge sort from chunks - [FINISHED]" << std::endl;
}

int main() {
  std::unique_ptr<std::vector<std::string>> chunks;
  chunks = std::make_unique<std::vector<std::string>>(splitFileToChunks("test-data/TestDataFile"));
  std::string sortedFileName = "sortedData";
  mergeSortFromChunks(chunks.get(), sortedFileName);
  return 0;
}
