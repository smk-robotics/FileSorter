/**
 * @file AbstractFileDataProvider.h
 * @author Smirnov Kirill <smk.robotics@gmail.com>
 * @brief AbstractFileDataProvider class.
 * @details Base template class for any data provider that can obtain data from file to any stl container.
 */
#pragma once

#include <iostream>
#include <fstream>
#include <string>

/**
 * @brief AbstractFileDataProvider class.
 * @tparam TElementType Element type for container with data obtained from file.
 * @tparam TContainerType Container type (one of STL) for container with data obtained from file.
 * @tparam TContainerParams Container parameters (std::allocator, etc.) for container with data obtained from file.
 */
template <typename TElementType, template <class, class ...> class TContainerType, class ... TContainerParams>
class AbstractFileDataProvider {
public:
    /**
     * @brief Virtual Abstract File Data Provider object destructor.
     */
    virtual ~AbstractFileDataProvider() = default;
    /**
     * @brief fileName function.
     * @return std::string Name of file with data that will be read.
     */
    std::string fileName() const noexcept {
        return mFileName;
    }
    /**
     * @brief getFileSize function.
     * @return long Size of file with data [byte].
     */
    long getFileSize() const {
        if (mFileName.empty()) {
            throw std::invalid_argument("[ERROR]:[AbstractFileDataProvider] - Filename is empty!");
        }
        std::ifstream inputFile(mFileName);
        if (!inputFile) {
            throw std::runtime_error("[ERROR]:[AbstractFileDataProvider] - Can't open \"" + mFileName + "\" file!");
        }
        inputFile.seekg(0, inputFile.end);
        long fileSize = inputFile.tellg();
        inputFile.close();
        return fileSize;
    }
    /**
     * @brief currentCharacterPosition function.
     * @return long Current character position in file with data.
     */
    long currentCharacterPosition() const noexcept {
        return mCurrentCharacterPosition;
    }
    /**
     * @brief setCurrentCharacterPosition function.
     * @param[in] characterPosition Desirable character position in file with data.
     */
    void setCurrentCharacterPosition(const unsigned long &characterPosition) {
        if (characterPosition <= mFileSize) {
            mCurrentCharacterPosition = characterPosition;
        } else {
             throw std::out_of_range("[ERROR]:[AbstractFileDataProvider] - Character position out of file!");
        }
    }
    /**
     * @brief finish function.
     * @return true If current character position equal last character position in file with data.
     * @return false If current character position not equal last character position in file with data..
     */
    bool finish() {
        return mCurrentCharacterPosition >= mFileSize;
    }
    /**
     * @brief GetDataFromFile function.
     * @return TContainerType<TElementType> Given type stl container with data obtained from file.
     */
    virtual TContainerType<TElementType> GetDataFromFile() = 0;

protected:
    std::string mFileName;                   /**< Name of file with data that will be obtained. */
    unsigned long mFileSize;                 /**< Size of file with data data that will be obtained. */
    unsigned long mDataCountLimit;           /**< Number of elements that will be obtained in each time. */
    unsigned long mCurrentCharacterPosition; /**< Current character position in file with data. */
};
