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
constexpr uint8_t dataBufferSize = 4;         // Buffer size to read data from given file (bytes).
constexpr float perfomanceCoefficient = 0.9 ; // Persentage of full RAM size use.
constexpr uint32_t chunkSizeLimit = (pow(1024,2) * maxRamSize / dataBufferSize) * perfomanceCoefficient;

template <typename T>
inline void showChunk(const T &chunk) noexcept {
  for (const auto &element:chunk) {
    std::cout << element << std::endl;
  }
}

template <typename T>
inline void writeDataToFile(const T &data, const std::string &fileName) noexcept {
  std::ofstream outputFile(fileName);
  for (const auto &element:data) {
    outputFile << element;
  }
  outputFile.close();
}

template <>
inline void writeDataToFile<std::string>(const std::string &data, const std::string &fileName) noexcept {
  std::ofstream outputFile(fileName, std::ios::binary | std::ios::ate);
  outputFile << data;
  outputFile.close();
}

// Just delete file nothing else.
inline void deleteFile(const std::string &fileName) {
  if (remove(fileName.c_str()) == 0) {
    std::cout << std::setw(80) << std::left <<
          "[FileSorter] - Deleting file \"" + fileName + "\" file:" << std::setw(10) <<
                                                                          std::right << "[FINISHED]" << std::endl;
  } else {
    std::cerr << std::setw(80) << std::left <<
          "[FileSorter] - Can't delete \"" + fileName + "\" file:" << std::setw(10) <<
                                                                         std::right << "[ERROR]" << std::endl;
  }
}

// Split data from given file to sorted chunks (files).
std::multimap<std::string, std::pair<std::string, unsigned long>> splitFileToChunks(const std::string &fileName) noexcept {
  std::cout << std::setw(80) << std::left <<
            "[FileSorter] - Splitting \"" + fileName + "\" file to chunks:" << std::setw(10) <<
                                                                            std::right << "[START]" << std::endl;
  std::string currentChunkName;
  std::multimap<std::string, std::pair<std::string, unsigned long>> chunksList;
  char charBuffer[dataBufferSize + 1];      // Buffer for readed data.
  std::multiset<std::string> sortedDataSet; // Sorted chunk of data from given file.
  std::ifstream originFile(fileName);       // Open given file to read data.
  auto currentChunkIndex = 0;               // Index of current chunk.
  if (originFile) {                         // Check that given file is exist and successfully opened.
    while (!originFile.eof()) {
      originFile.read(charBuffer, dataBufferSize);                       // Read data from file with unsorted data.
      sortedDataSet.insert(charBuffer);                                  // Add data to sorted container.
      if (sortedDataSet.size() >= chunkSizeLimit) {                      // Check sorted container size.
        currentChunkName = std::to_string(currentChunkIndex);
        // Store first element of sorted data, name of chunk, and number of readed bytes:
        chunksList.insert({*sortedDataSet.begin(), {currentChunkName, dataBufferSize}});
        writeDataToFile(sortedDataSet, currentChunkName);                // Output sorted chunk to external file.
        sortedDataSet.erase(sortedDataSet.begin(), sortedDataSet.end()); // Clear sorted chunk to repeat process.
        ++currentChunkIndex;
      }
    }
  } else {
    std::cerr << std::setw(80) << std::left <<
    "[FileSorter] - Can't open file \"" + fileName + "\":" << std::setw(10) << std::right << "[ERROR]" << std::endl;
    return {};
  }
  currentChunkName = std::to_string(currentChunkIndex);
  chunksList.insert({*sortedDataSet.begin(), {currentChunkName, dataBufferSize}});
  writeDataToFile(sortedDataSet, currentChunkName);
  originFile.close();
  std::cout << std::setw(80) << std::left <<
            "[FileSorter] - Splitting file to chunks:" << std::setw(10) << std::right << "[FINISHED]" << std::endl;
  return chunksList;
}


void mergeSortFromChunks(std::multimap<std::string, std::pair<std::string, unsigned long>> &chunksList,
                         const std::string &sortedFileName) noexcept {
  std::cout << std::setw(80) << std::left <<
        "[FileSorter] - Merging " + std::to_string(chunksList.size()) + " chunks to \"" + sortedFileName + "\" file:" <<
                                                                 std::setw(10) << std::right << "[START]" << std::endl;
  char charBuffer[dataBufferSize + 1];      // Buffer for readed data.
  std::ofstream resultFile(sortedFileName); // Open result file to write sorted data.
  while (!chunksList.empty()) {             // Read data from chunks list untill it contains anything.
      resultFile << chunksList.begin()->first;
      // Store parameters from smallest element's chunk:
      unsigned long currentElementPosition = chunksList.begin()->second.second;
      std::string currentChunkName = chunksList.begin()->second.first;
      std::ifstream currentChunkFile(chunksList.begin()->second.first); // Open chunk with previous smallest element.
      currentChunkFile.seekg(chunksList.begin()->second.second);        // Set required position iN file.
      chunksList.erase(chunksList.begin());                             // Remove smallest element from sorted set.
      if (currentChunkFile.read(charBuffer, dataBufferSize)) {          // Read new element from chunk and add it to set.
        chunksList.insert({charBuffer, {currentChunkName, currentElementPosition + dataBufferSize}});
        currentChunkFile.close();
      } else {
        currentChunkFile.close();
        deleteFile(currentChunkName);
      }
  }
  resultFile.close();
  std::cout << std::setw(80) << std::left <<
           "[FileSorter] - Merging chunks to file:" << std::setw(10) << std::right << "[FINISHED]" << std::endl;
}

int main() {
  std::string originDataFile = "test-data/TestDataFile";
  std::string sortedDataFile = "sortedData";
  std::multimap<std::string, std::pair<std::string, unsigned long>> chunks;
  chunks = splitFileToChunks(originDataFile);
  if (!chunks.empty()) {
    mergeSortFromChunks(chunks, sortedDataFile);
  }
  return 0;
}
