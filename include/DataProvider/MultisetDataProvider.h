#include <set>
#include <stdexcept>
#include "AbstractFileDataProvider.h"

#pragma once

template <typename TElementType> class MultisetDataProvider : public AbstractFileDataProvider<TElementType,
                                                                                              std::multiset>
{
public:
    MultisetDataProvider(const std::string &fileName, const uint64_t &countLimit) {
        this->mCurrentCharacterPosition = 0;
        this->mFileName = fileName;
        this->mFileSize = this->getFileSize();
        this->mDataCountLimit = countLimit;
    }
    std::multiset<TElementType> GetDataFromFile() override {
        if (this->mFileName.empty()) {
            std::cerr << "[ERROR][MultisetDataProvider] - Skip reading data. Filename is empty!" << std::endl;
            return {};
        }
        std::ifstream inputFile(this->mFileName);
        if (!inputFile) {
            throw std::runtime_error("[MultisetDataProvider] - Can't open " + this->mFileName + " file!");
            return {};
        }
        inputFile.seekg(this->mCurrentCharacterPosition);   // Setup symbol position in input stream.
        char charBuffer[sizeof(TElementType) + 1]; // Additional symbol (+1) for end of row symbol.
        std::multiset<TElementType> readedData;
        while (readedData.size() <= this->mDataCountLimit || inputFile.eof()) {
            inputFile.read(charBuffer, sizeof(TElementType));
            readedData.insert(static_cast<TElementType>(*charBuffer));
            this->setCurrentCharacterPosition(inputFile.tellg());
        }
        inputFile.close();
        return readedData;
    }
};
