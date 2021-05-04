/**
 * @file AbstractFileSplitter.h
 * @author Smirnov Kirill <smk.robotics@gmail.com>
 * @brief AbstractFileSplitter class.
 * @details Base template class for object that split file with data to smaller files (chunks).
 */
#pragma once

#include "Chunk.h"

namespace fle_srtr {

/**
 * @brief AbstractFileSplitter class.
 * @details Split file with data to smaller files (chunks) and make lists of it.
 * @tparam T Data type stored in file. 
 */
template <class TChunkType> class AbstractFileSplitter {
public:
    /**
     * @brief splitFileToChunks function.
     * @param[in] originFileName Name of file with data. 
     * @return std::vector<Chunk<T>> Custom object with data obtained from given file.
     */
    virtual std::vector<TChunkType> splitFileToChunks(const std::string &originFileName) = 0;
    /**
     * @brief Virtual Abstract File Splitter object destructor.
     */
    virtual ~AbstractFileSplitter() = default;
    /**
     * @brief fileValid function.
     * @param[in] filename Name of file that need to be check. 
     * @return true If file exists and accessible.
     * @return false If filename is empty or file not exist or valid.
     */
    bool fileValid(const std::string &filename) const noexcept {
        if (filename.empty()) {
            std::cerr << "[ERROR][AbstractFileSplitter] - Filename is empty." << std::endl;
            return false;
        }
        if (!std::ifstream(filename)) {
            std::cerr << "[ERROR][AbstractFileSplitter] - Can't open \"" << filename << "\"." << std::endl;
            return false;
        }
        return true;
    }
};

} // fle_srtr namespace.
