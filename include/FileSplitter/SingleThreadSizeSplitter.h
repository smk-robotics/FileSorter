/**
 * @file SingleThreadSizeSplitter.h
 * @author Smirnov Kirill <smk.robotics@gmail.com>
 * @brief SingleThreadSizeSplitter class.
 * @details Class for object that splits file to multiset chunks with any given type.
 */
#pragma once

#include <fstream>
#include <vector>
#include "AbstractFileSplitter.h"
#include "MultisetDataProvider.h"

namespace fle_srtr {

template <typename TElementType> 
class SingleThreadSizeSplitter : public AbstractFileSplitter<Chunk> {
public:
    explicit SingleThreadSizeSplitter(const uint16_t chunkSizeMb) 
        : mChunkElementsNumberLimit(1000 * 1000 * chunkSizeMb / sizeof(TElementType)) {};
    std::vector<Chunk> splitFileToChunks(const std::string &filename) override {
        if (!this->fileValid(filename)) {
            throw std::runtime_error("[ERROR][SingleThreadSizeSplitter] - Filename not valid!");
        }
        std::vector<Chunk> chunks;
        MultisetDataProvider<TElementType> multisetDataProvider(filename, mChunkElementsNumberLimit);
        auto currentChunkIndex = 0; /**< Index of current chunk. */
        while (!multisetDataProvider.finish()) {
            chunks.push_back(Chunk(std::to_string(currentChunkIndex), multisetDataProvider.GetDataFromFile()));
            currentChunkIndex += 1;
        }
        return chunks;
    };
    ~SingleThreadSizeSplitter() = default;
private:
    uint32_t mChunkElementsNumberLimit; /**< Number of elements in buffer. */
};

} // fle_srtr namespace.