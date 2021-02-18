#include <iostream>
#include <fstream>
#include <iomanip>
#include <memory>
#include <set>
#include <map>
#include <math.h>
#include <time.h>
#include <string>
#include <cstring>
#include "FileSplitter/SizeSingleThreadSplitter.h"

namespace {
    constexpr uint16_t maxRamSize = 2;          // Max size of chunk in external sorting (MegaBytes).
}

//// Merge sorting algorithm. Get chunks with sorted parts of data and merge it in result file.
//void mergeSortFromChunks(std::multimap<std::string, std::pair<std::string, unsigned long>> &chunksList,
//                         const std::string &sortedFileName) noexcept {
//  clock_t startTime = clock();              // Get current time to calculate time taken for algorithm.
//  char charBuffer[dataBufferSize + 1];      // Buffer for readed data.
//  std::ofstream resultFile(sortedFileName); // Open result file to write sorted data.
//  bool spacerFlag = true;
//  while (!chunksList.empty()) {             // Read data from chunks list untill it contains anything.
//    std::cout << "\33[2K\r" << std::setw(80) << std::left <<
//      "[FileSorter] - Merging " + std::to_string(chunksList.size()) + " chunks to \"" + sortedFileName + "\" file:" <<
//                                   std::setw(5) << std::right << "[" << (spacerFlag ?  std::string("<<<") :  std::string("<<<<")) << "]" << std::flush;
//      resultFile << chunksList.begin()->first;
//      // Store parameters from smallest element's chunk:
//      unsigned long currentElementPosition = chunksList.begin()->second.second;
//      std::string currentChunkName = chunksList.begin()->second.first;
//      std::ifstream currentChunkFile(chunksList.begin()->second.first); // Open chunk with previous smallest element.
//      currentChunkFile.seekg(chunksList.begin()->second.second);        // Set required position in file.
//      chunksList.erase(chunksList.begin());                             // Remove smallest element from sorted set.
//      if (currentChunkFile.read(charBuffer, dataBufferSize)) {          // Read new element from chunk and add it to set.
//        chunksList.insert({charBuffer, {currentChunkName, currentElementPosition + dataBufferSize}});
//        currentChunkFile.close();
//      } else {
//        currentChunkFile.close();
//        deleteFile(currentChunkName);
//      }
//      spacerFlag = !spacerFlag;
//  }
//  resultFile.close();
//  std::cout << "\33[2K\r" << std::setw(80) << std::left <<
//           "[FileSorter] - Merging chunks to file:" << std::setw(10) << std::right << "[FINISHED]" << std::flush;
//  std::cout << std::endl;
//  double timeTaken = (clock() - startTime) /
//                                       static_cast<double>(CLOCKS_PER_SEC); // Calculate time taken for algorithm work.
//  std::cout << std::setw(80) << std::left <<
//            "[FileSorter] - Time taken to megring chunks (seconds):" << std::setw(10) << std::right <<
//                                                              "[" + std::to_string(timeTaken) + "]" << std::endl;
//}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "[ERROR]: Need to pass origin/result filenames in command line arguments" << std::endl;
    return 1;
  }
  if (static_cast<std::string>(argv[1]) == "-h" || static_cast<std::string>(argv[1]) == "--help") {
    std::cout << "Pass origin and result file names in command line arguments." << std::endl;
    std::cout << "Example: fileSorter <UnsorteredDataFilename> <SortedDataFileName>" << std::endl;
    return 0;
  }
  [[maybe_unused]] auto originDataFile = argv[1];
  [[maybe_unused]] auto sortedDataFile = argv[2];

//  SingleThreadBySizeSplitter<uint32_t> single(maxRamSize);
//  std::shared_ptr<AbstractFileSplitter<uint32_t>> fileSplitter =
//                                                   std::make_shared<SingleThreadBySizeSplitter<uint32_t>>(maxRamSize);
//  std::vector<Chunk<uint32_t>> chunks = fileSplitter->splitFileToChunks(originDataFile);
  return 0;
}
