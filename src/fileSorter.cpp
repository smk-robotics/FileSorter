#include <iostream>
#include <fstream>
#include <iomanip>
#include <memory>
#include <set>
#include <map>
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

template <>
inline void writeDataToFile<std::string>(const std::string &data, const std::string chunkFileName) noexcept {
  std::ofstream chunkFile(chunkFileName);
  chunkFile << data;
  chunkFile.close();
}

inline void deleteFile(const std::string &fileName) {
  if (!remove(fileName.c_str()) == 0) {
    std::cerr << std::setw(80) << std::left <<
    "[FileSorter] - Can't remove \"" + fileName + "\" file:" << std::setw(10) << std::right << "[ERROR]" << std::endl;
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

void mergeSortFromChunks(std::unordered_map<std::string, unsigned long> &chunksList,
                         const std::string &sortedFileName) noexcept {
  std::ifstream resultFile(sortedFileName); // Open file to load result sorted data.
  char charBuffer[charBufferSize + 1];      // Buffer for readed data.
  std::multimap<std::string, std::string> sortedData; // Sorted part of data from all chunks.
  auto singleChunkDataCountLimit = chunkSizeLimit / chunksList.size();

  // for (auto chunk = chunksList.begin(); chunk != chunksList.end(); ++chunk) {
  //   std::ifstream currentChunkFile(chunk->first); // Open every chunk for read.
  //   currentChunkFile.seekg(chunk->first);        // Go to last readed buffer position in chunk.
  //   if (!currentChunkFile.eof()) {
  //     currentChunkFile.read(charBuffer, charBufferSize);
  //     sortedData.insert({charBuffer, chunk->second});
  //     chunk->second += charBufferSize;
  //   } else {
  //     deleteFile(chunk->first);                  // Remove chunk file from system.
  //     chunk = chunksList.erase(chunk);           // Remove chunk from list.
  //   }
  // }

  // while (!chunksList.empty()) {             // Read data from chunks untill there is any chunks in list.
  //   for (auto chunk = chunksList.begin(); chunk != chunksList.end(); ++chunk) {
  //     std::ifstream currentChunkFile(chunk->first); // Open every chunk for read.
  //     currentChunkFile.seekg(chunk->second);        // Go to last readed buffer position in chunk.
  //     auto currentChunkDataCount = 0;               // Reset readed data counter.
  //     sortedData.clear();
  //     // Read data from the chunk until reach limit or end of file:
  //     while (!currentChunkFile.eof() || currentChunkDataCount < singleChunkDataCountLimit) {
  //       currentChunkFile.read(charBuffer, charBufferSize);
  //       sortedData.insert(charBuffer);
  //       chunk->second += charBufferSize;           // Update last readed buffer position in chunk.
  //       ++currentChunkDataCount;
  //     }
  //     writeDataToFile(sortedData, sortedFileName); // Load sorted data to result file.
  //     currentChunkFile.close();
  //     if (currentChunkFile.eof()) {                // Check reach end of chunk file end.
  //
  //     }
  //   }
  // }
}

int main() {
  std::string originDataFile = "test-data/TestDataFile";
  std::string sortedDataFile = "sortedData";
  std::unordered_map<std::string, unsigned long> chunks;
  std::multimap<std::string, std::pair<std::string, unsigned long>> superCunks;
  chunks = splitFileToChunks(originDataFile);
  if (!chunks.empty()) {
    std::cout << std::setw(80) << std::left <<
              "[FileSorter] - Splitting \"" + originDataFile + "\" file to chunks:" << std::setw(10) <<
                                                                              std::right << "[FINISHED]" << std::endl;
    mergeSortFromChunks(chunks, sortedDataFile);
    std::cout << std::setw(80) << std::left <<
             "[FileSorter] - Merge " + std::to_string(chunks.size()) + " chunks to \"" + sortedDataFile + "\" file:" <<
                                                            std::setw(10) << std::right << "[FINISHED]" << std::endl;
    if (chunks.empty()) {
    std::cout << std::setw(80) << std::left <<
              "[FileSorter] - Deleting all chunk files:" << std::setw(10) << std::right << "[FINISHED]" << std::endl;
    }
  }
  return 0;
}
