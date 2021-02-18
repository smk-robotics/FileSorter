#include <iostream>
#include <fstream>
#include <set>
#include <math.h>
#include "SizeSingleThreadSplitter.h"
#include "DataProvider/MultisetDataProvider.h"

template <class T> SingleThreadBySizeSplitter<T>::SingleThreadBySizeSplitter(const uint16_t size) :
    mChunkElementsNumberLimit(1000 * 1000 * size / sizeof(T)) {
}

template <class T> std::vector<Chunk<T>> SingleThreadBySizeSplitter<T>::splitFileToChunks(
                                                                                  const std::string &originFileName) {
    std::vector<Chunk<T>> chunks;
    MultisetDataProvider multisetDataProvider(originFileName, mChunkElementsNumberLimit);
    auto currentChunkIndex = 0; // Index of current chunk.
    while (multisetDataProvider.finish()) {
        Chunk<T> currenChunk(std::to_string(currentChunkIndex), multisetDataProvider.GetDataFromFile());
        chunks.push_back(currenChunk);
    }
    return chunks;
}
