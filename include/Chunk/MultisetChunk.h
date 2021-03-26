/**
 * @file MultisetChunk.h
 * @author Smirnov Kirill <smk.robotics@gmail.com>
 * @brief AbstractChunk class.
 * @details Chunk class that stores any type of data in std::multiset container.
 */
#include <set>
#include "AbstractChunk.h"

#pragma once
/**
 * @brief MultisetChunk class.
 * @tparam TElementType Type of elemnts that will be stored in std::multiset container.
 */
template <typename TElementType> class MultisetChunk : public AbstractChunk<TElementType, std::multiset> {
public:
    /**
     * @brief Multiset Chunk object constructor.
     * @param[in] chunkFileName Name for chunk (also name for file where chunk will be stored). 
     */
    MultisetChunk(const std::string &chunkFileName) {
        this->setChunkFileName(chunkFileName);
    }
    /**
     * @brief Multiset Chunk object constructor.
     * @details Create multiset chunk and store given data to chunk binary file.
     * @param[in] chunkFileName Name for chunk (also name for file where chunk will be stored). 
     * @param[in] data Chunk data that will be stored in chunk file.
     */
    MultisetChunk(const std::string &chunkFileName, const std::multiset<TElementType> &data) {
        this->setChunkFileName(chunkFileName);
        writeDataToChunkFile(data);
    }
    /**
     * @brief writeDataToChunkFile function.
     * @details Write data from given container to binary file.
     * @param[in] data Container with sorted data that will be saved in file. 
     * @return true If data successfully write to file. 
     * @return false If something wrong with file (not exist, can't open, etc) or data (empty).
     */
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
