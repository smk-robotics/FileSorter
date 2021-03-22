/**
 * @file AbstractChunk.h
 * @author Smirnov Kirill <smk.robotics@gmail.com>
 * @brief AbstractChunk class.
 * @details Base template class for any chunk. Specific сhunk class can inherit from that class and specify stl
 * container for stored data.
 */
#include <iostream>
#include <fstream>
#include <string>

#pragma once

template<typename TElementType, template<class, class...> class TContainer, class... TContainerParameters>
class AbstractChunk {
public:
    AbstractChunk() = default;
    virtual ~AbstractChunk() = default;
    /**
     * @brief createChunkFile
     * @details Creates binary chunk file.
     */
    void createChunkFile() const {
        if (mChunkFileName.empty()) {
            std::cerr << "[ERROR][ABSTRACT_CHUNK] - Skip creating chunk file. Filename is empty." << std::endl;
            return;
        }
        std::ofstream chunkFile(mChunkFileName);
        if (chunkFile.good()) {
            chunkFile.close();
        } else {
            std::cerr << "[ERROR][CHUNK] - Can't create \"" << mChunkFileName << "\" chunk file." << std::endl;
        }
        return;
    }
    /**
     * @brief deleteChunkFile
     * @details Delete existing binary chunk file.
     * @return True if successfully delete binary chunk file. False if something went wrong.
     */
    bool deleteChunkFile() const {
        if (mChunkFileName.empty()) {
            std::cerr << "[ERROR][CHUNK] - Skip deleting chunk file. Filename is empty." << std::endl;
            return false;
        }
        if (std::remove(mChunkFileName.c_str()) == 0) {
            return true;
        } else {
            std::cerr << "[ERROR][CHUNK] - Can't delete \"" << mChunkFileName << "\" chunk file." << std::endl;
            return false;
        }
    }
    /**
     * @brief chunkFileName
     * @return Current chunk filename value.
     */
    std::string chunkFileName() const noexcept { return mChunkFileName; }
    /**
     * @brief setChunkFileName
     * @details Setter for chunk filename value. Don't rename existing chunkfile.
     * @param[in] chunkFileName Given name for chunk file.
     */
    void setChunkFileName(const std::string &chunkFileName) noexcept { mChunkFileName = chunkFileName; }
    /**
     * @brief writeDataToChunkFile
     * @details Pure virtual method that writes data to file. Need to be specified in child class with specific
     * container for data.
     * @param data[in] Given data that will write to binary chunk file.
     * @return True in successfully write data to binary file. False if something gone wrong.
     */
    virtual bool writeDataToChunkFile(const TContainer<TElementType> &data) const = 0;

protected:
    std::string mChunkFileName; /**< Name for chunk. Also use as chunk's filename. */
};
