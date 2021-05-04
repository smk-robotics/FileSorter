/**
 * @file Chunk.h
 * @author Smirnov Kirill <smk.robotics@gmail.com>
 * @brief Chunk class.
 * @details Class for chunk that stores name of chunk and create/delete chunk binary file.
 */
#pragma once

#include "DataWriter.h"

namespace fle_srtr {
/**
 * @brief Chunk class.
 * @details Stores chunk filename and methods for create/delete chunk file with sorted data from any stl container.
 * @attention Not stores container with data!
 */
class Chunk {
public:
    /**
     * @brief Constructor for new Chunk object.
     * @param[in] filename Name of chunk. Also use as filename for binary file with data from given container. 
     */
    Chunk(const std::string &filename)
    : mChunkFileName(filename) {}
    /**
     * @brief Constructor for new Chunk object.
     * @tparam TContainerType Type of container with data (vector, set, multiset, etc.).
     * @tparam TElementType Type of data elements in container (int, float, double, etc.).
     * @param[in] filename Name of chunk. Also use as filename for binary file with data from given container. 
     * @param[in] data Container with data that will be stored in chunk binary file.
     */
    template<template<class ...> class TContainerType, class TElementType> 
    Chunk(const std::string &filename, [[maybe_unused]] const TContainerType<TElementType> &data) 
    : mChunkFileName(filename) {
        writeDataToChunkFile(data);
    }
    /**
     * @brief Chunk object destructor.
     */
    ~Chunk() = default;
    /**
     * @brief createChunkFile function.
     * @details Creates binary chunk file.
     */
    void createChunkFile() const {
        if (mChunkFileName.empty()) {
            std::cerr << "[ERROR][Chunk] - Skip creating chunk file. Filename is empty." << std::endl;
            return;
        }
        std::ofstream chunkFile(mChunkFileName);
        if (chunkFile.good()) {
            chunkFile.close();
        } else {
            std::cerr << "[ERROR][Chunk] - Can't create \"" << mChunkFileName << "\" chunk file." << std::endl;
        }
        return;
    }
    /**
     * @brief deleteChunkFile function.
     * @details Delete existing binary chunk file.
     * @return True if successfully delete binary chunk file. False if something went wrong.
     */
    bool deleteChunkFile() const {
        if (mChunkFileName.empty()) {
            std::cerr << "[ERROR][Chunk] - Skip deleting chunk file. Filename is empty." << std::endl;
            return false;
        }
        if (std::remove(mChunkFileName.c_str()) == 0) {
            return true;
        } else {
            std::cerr << "[ERROR][Chunk] - Can't delete \"" << mChunkFileName << "\" chunk file." << std::endl;
            return false;
        }
    }
    /**
     * @brief chunkFileName function.
     * @return Current chunk filename value.
     */
    std::string chunkFileName() const noexcept { return mChunkFileName; }
    /**
     * @brief setChunkFileName function.
     * @details Setter for chunk filename value. Don't rename existing chunkfile.
     * @param[in] chunkFileName Given name for chunk file.
     */
    void setChunkFileName(const std::string &chunkFileName) noexcept { mChunkFileName = chunkFileName; }
    /**
     * @brief writeDataToChunkFile function.
     * @details Create binary file and write given data to it.
     * @param data[in] Given data that will write to binary chunk file.
     * @return True in successfully write data to binary file. False if something gone wrong.
     */
    template<template<class ...> class TContainerType, class TElementType> 
    bool writeDataToChunkFile([[maybe_unused]] const TContainerType<TElementType> &data) {
        return mDataWriter.writeDataToFile(mChunkFileName, data);
    }

protected:
    std::string mChunkFileName; /**< Name for chunk. Also use as chunk's filename. */
    DataWriter mDataWriter;     /**< Object that write data from container to binary file. */
};

} // fle_srtr namespace.
