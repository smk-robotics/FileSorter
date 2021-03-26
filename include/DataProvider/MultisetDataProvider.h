/**
 * @file MultisetDataProvider.h
 * @author Smirnov Kirill <smk.robotics@gmail.com>
 * @brief MultisetDataProvider class.
 * @details Class for data provider that obtain data from file to any element type std::multiset container.
 */
#include <set>
#include <stdexcept>
#include "AbstractFileDataProvider.h"

#pragma once
/**
 * @brief MultisetDataProvider class.
 * @details Data provider that obtain data from file to any element type std::multiset container.
 * @tparam TElementType Element type for std::multiset data container.
 */
template <typename TElementType> class MultisetDataProvider : public AbstractFileDataProvider<TElementType,
                                                                                              std::multiset> {
public:
    /**
     * @brief Multiset Data Provider object constructor.
     * @param[in] fileName Name of file with data that will be obtained.
     * @param[in] countLimit Number of element in container with data. 
     */
    MultisetDataProvider(const std::string &fileName, const uint64_t &countLimit) {
        if (!this->mFileName.empty()) {
            throw std::runtime_error("[ERROR][MultisetDataProvider] - Filename is empty!");
        }
        this->mCurrentCharacterPosition = 0;
        this->mFileName = fileName;
        this->mFileSize = this->getFileSize();
        if (this->mFileSize == 0) {
            throw std::runtime_error("[ERROR][MultisetDataProvider] - File is empty!");
        }
        if (countLimit == 0) {
            throw std::runtime_error("[ERROR][MultisetDataProvider] - Data count limit is equal 0!");
        }
        this->mDataCountLimit = countLimit;
    }
    /**
     * @brief GetDataFromFile function.
     * @details Read data from file to std::multiset container with any element type.
     * @return std::multiset<TElementType>  Container with data obtained from file.
     */
    std::multiset<TElementType> GetDataFromFile() override {
        std::ifstream inputFile(this->mFileName);
        if (!inputFile) {
            throw std::runtime_error("[MultisetDataProvider] - Can't open " + this->mFileName + " file!");
        }
        inputFile.seekg(this->mCurrentCharacterPosition);   // Setup symbol position in input stream.
        char charBuffer[sizeof(TElementType) + 1]; // Additional symbol (+1) for end of row symbol.
        std::multiset<TElementType> readedData;
        while (readedData.size() < this->mDataCountLimit || inputFile.eof()) {
            inputFile.read(charBuffer, sizeof(TElementType));
            readedData.insert(static_cast<TElementType>(*charBuffer));
            this->setCurrentCharacterPosition(inputFile.tellg());
        }
        inputFile.close();
        return readedData;
    }
};
