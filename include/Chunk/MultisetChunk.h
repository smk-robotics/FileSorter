#include <set>
#include "AbstractChunk.h"

#pragma once

template <typename TElementType> class MultisetChunk : public AbstractChunk<TElementType, std::multiset> {
public:
    MultisetChunk(const std::string &chunkFileName) {
        this->setChunkFileName(chunkFileName);
    }
    MultisetChunk(const std::string &chunkFileName, const std::multiset<TElementType> &data) {
        this->setChunkFileName(chunkFileName);
        writeDataToChunkFile(data);
    }
    bool writeDataToChunkFile(const std::multiset<TElementType> &data) const override {
        if (data.empty()) {
            std::cerr << "[ERROR][CHUNK] - Skip writting data to file. Data is empty." << std::endl;
            return false;
        }
        if (this->mChunkFileName.empty()) {
            std::cerr << "[ERROR][CHUNK] - Skip writting data to file. Chunk filename is empty." << std::endl;
            return false;
        }
        std::ofstream outputFile(this->mChunkFileName);
        if (!outputFile) {
            std::cerr << "[ERROR][CHUNK] - Can't write data to \"" << this->mChunkFileName << "\" chunk file." << std::endl;
            return false;
        }
        for (const auto &element : data) {
            outputFile << element;
        }
        outputFile.close();
        return true;
    }
};
