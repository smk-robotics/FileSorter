#include <iostream>
#include <fstream>
#include <iomanip>
#include <memory>
#include <set>
#include <unordered_map>
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
inline void writeDataToFile(const T &data, const std::string chunkFileName) noexcept {
  std::ofstream chunkFile(chunkFileName);
  for (const auto &element:data) {
    chunkFile << element;
  }
  chunkFile.close();
}

template <typename T>
inline void deleteFiles(T &filesMap) {
  for (auto i = 0; i <= filesMap.size() + 1; ++i) {
    if (remove(filesMap.begin()->first.c_str()) == 0) {
      filesMap.erase(filesMap.begin());
    } else {
      std::cerr << std::setw(80) << std::left <<
      "[FileSorter] - Can't remove \"" + filesMap.begin()->first + "\" chunk:" << std::setw(10) << std::right <<
                                                                                                "[ERROR]" << std::endl;
    }
  }
}

// Split data from given file to sorted chunks (files).
std::unordered_map<std::string, unsigned long> splitFileToChunks(const std::string &fileName) noexcept {
  std::string currentChunkName;
  std::unordered_map<std::string, unsigned long> chunksList;
  char charBuffer[charBufferSize + 1];    // Buffer for readed data.
  std::multiset<std::string> sortedChunk; // Sorted chunk of data from given file.
  std::ifstream originFile(fileName);     // Open given file to read data.
  auto currentChunkIndex = 0;             // Index of current chunk.
  if (originFile) {                       // Check that given file is exist and successfully opened.
    while (!originFile.eof()) {
      originFile.read(charBuffer, charBufferSize);                // Read data from file with unsorted data.
      sortedChunk.insert(charBuffer);                             // Add data to sorted container.
      if (sortedChunk.size() >= chunkSizeLimit) {                 // Check sorted container size.
        currentChunkName = std::to_string(currentChunkIndex);
        chunksList.insert({currentChunkName, 0});                   // Store name of chunk and number of readed bytes.
        writeDataToFile(sortedChunk, currentChunkName);           // Output sorted chunk to external file.
        sortedChunk.erase(sortedChunk.begin(), sortedChunk.end()); // Clear sorted chunk to repeat process.
        ++currentChunkIndex;
      }
    }
  } else {
    std::cerr << std::setw(80) << std::left <<
    "[FileSorter] - Can't open file \"" + fileName + "\":" << std::setw(10) << std::right << "[ERROR]" << std::endl;
    return {};
  }
  currentChunkName = std::to_string(currentChunkIndex);
  chunksList.insert({currentChunkName, 0});
  writeDataToFile(sortedChunk, currentChunkName);
  originFile.close();
  return chunksList;
}

void mergeSortFromChunks(const std::unordered_map<std::string, unsigned long> &chunksList,
                         const std::string &sortedFileName) noexcept {
  std::ifstream resultFile(sortedFileName); // Open file to load result sorted data.
  char charBuffer[charBufferSize + 1];      // Buffer for readed data.
  std::multiset<std::string> sortedData;    // Sorted part of data from all chunks.
  unsigned long iterationIndex = 0;
  for (const auto &chunk:chunksList) {
    std::ifstream currentChunkFile(chunk.first);
    currentChunkFile.seekg(chunk.second);
    while (!currentChunkFile.eof()) {
      currentChunkFile.read(charBuffer, charBufferSize);
      sortedData.insert(charBuffer);
    }
    writeDataToFile(sortedData, sortedFileName);
    currentChunkFile.close();
    ++iterationIndex;
  }
}

int main() {
  std::string originFile = "test-data/TestDataFile";
  std::unordered_map<std::string, unsigned long> chunks;
  chunks = splitFileToChunks(originFile);

  if (chunks.empty()) {
      return 0;
  }
  std::cout << std::setw(80) << std::left <<
              "[FileSorter] - Splitting \"" + originFile + "\" file to chunks:" << std::setw(10) <<
                                                                              std::right << "[FINISHED]" << std::endl;
  std::string sortedFileName = "sortedData";
  mergeSortFromChunks(chunks, sortedFileName);
  std::cout << std::setw(80) << std::left <<
               "[FileSorter] - Merge sorting from " + std::to_string(chunks.size()) + " chunks:" << std::setw(10) <<
                                                                              std::right << "[FINISHED]" << std::endl;
  deleteFiles(chunks);
  if (chunks.empty()) {
  std::cout << std::setw(80) << std::left <<
               "[FileSorter] - Deleting chunk files:" << std::setw(10) << std::right << "[FINISHED]" << std::endl;
  }
  return 0;
}
