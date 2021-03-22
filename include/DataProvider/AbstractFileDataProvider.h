#include <iostream>
#include <fstream>
#include <string>

#pragma once

template<typename TElementType, template<class, class...> class TConteinerType, class... TContainerParams>
class AbstractFileDataProvider
{
public:
    AbstractFileDataProvider() = default;
    virtual ~AbstractFileDataProvider() = default;
    std::string fileName() const noexcept {
        return mFileName;
    }
    void setFileName(const std::string &fileName) noexcept {
        mFileName = fileName;
    }
    long getFileSize() const {
        if (mFileName.empty()) {
            throw std::invalid_argument("[ERROR][AbstractFileDataProvider] - Filename is empty!");
        }
        std::ifstream inputFile(mFileName);
        if (!inputFile) {
            throw std::runtime_error("[ERROR][AbstractFileDataProvider] - Can't open \"" + mFileName + "\" file!");
        }
        inputFile.seekg(0, inputFile.end);
        long fileSize = inputFile.tellg();
        inputFile.close();
        return fileSize;
    }
    long currentCharacterPosition() const noexcept {
        return mCurrentCharacterPosition;
    }
    void setCurrentCharacterPosition(unsigned long characterPosition) {
        if (characterPosition <= mFileSize) {
            mCurrentCharacterPosition = characterPosition;
        } else {
             throw std::out_of_range("[ERROR][AbstractFileDataProvider] - Character position out of file!");
        }
    }
    bool finish() {
        return mCurrentCharacterPosition >= mFileSize ? true : false;
    }
    virtual TConteinerType<TElementType> GetDataFromFile() = 0;
protected:
    std::string mFileName;
    unsigned long mFileSize;
    unsigned long mDataCountLimit;
    unsigned long mCurrentCharacterPosition;
};
