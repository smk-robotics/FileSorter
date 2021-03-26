/**
 * @file SingleThreadSizeSplitter.h
 * @author Smirnov Kirill <smk.robotics@gmail.com>
 * @brief SingleThreadSizeSplitter class.
 * @details Class for object that splits file to multiset chunks with any given type.
 */
#include <fstream>
#include <vector>
#include "AbstractFileSplitter.h"
#include "MultisetChunk.h"
#include "MultisetDataProvider.h"

#pragma once

template <typename TElementType> 
class SingleThreadSizeSplitter : public AbstractFileSplitter<MultisetChunk<TElementType>> {
public:
    explicit SingleThreadSizeSplitter(const uint16_t chunkSizeMb) 
        : mChunkElementsNumberLimit(1000 * 1000 * chunkSizeMb / sizeof(TElementType)) {};
    std::vector<MultisetChunk<TElementType>> splitFileToChunks(const std::string &filename) override {
        if (!this->fileValid(filename)) {
            throw std::runtime_error("[ERROR][SingleThreadSizeSplitter] - Filename not valid!");
        }
        std::vector<MultisetChunk<TElementType>> chunks;
        MultisetDataProvider<TElementType> multisetDataProvider(filename, mChunkElementsNumberLimit);
        auto currentChunkIndex = 0; /**< Index of current chunk. */
        while (multisetDataProvider.finish()) {
            chunks.push_back(MultisetChunk<TElementType>(std::to_string(currentChunkIndex), 
                                                                        multisetDataProvider.GetDataFromFile()));
            currentChunkIndex += 1;
        }
        return chunks;
    };
    ~SingleThreadSizeSplitter() = default;
private:
    uint32_t mChunkElementsNumberLimit; /**< Number of elements in buffer. */
};
