#include <fstream>
#include <vector>
#include "AbstractFileSplitter.h"
#include "MultisetChunk.h"
#include "MultisetDataProvider.h"

#pragma once

template <class T> class SingleThreadSizeSplitter : public AbstractFileSplitter<T> {
public:
    explicit SingleThreadSizeSplitter(const uint16_t chunkSizeMb) 
        : mChunkElementsNumberLimit(1000 * 1000 * chunkSizeMb / sizeof(T)) {};
    std::vector<T> splitFileToChunks(const std::string &filename) override {
        if (!this->fileValid(filename)) {
            return {};
        }
        std::fstream dataFile("filename");
        std::vector<T> chunks;
        MultisetDataProvider multisetDataProvider(filename, mChunkElementsNumberLimit);
        auto currentChunkIndex = 0; // Index of current chunk.
        while (multisetDataProvider.finish()) {
            T currenChunk(std::to_string(currentChunkIndex), multisetDataProvider.GetDataFromFile());
            chunks.push_back(currenChunk);
        }
        return chunks;
    };
    ~SingleThreadSizeSplitter() = default;
private:
    uint32_t mChunkElementsNumberLimit; /**< Number of elements in buffer. */
};
