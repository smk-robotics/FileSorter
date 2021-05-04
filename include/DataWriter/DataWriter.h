#pragma once 

#include <algorithm>
#include <fstream>
#include <iostream>
#include <typeindex>
#include <set>
#include <string>
#include <vector>

namespace fle_srtr {

class DataWriter {
public:
    DataWriter() {
        mValidContainerElementTypes.emplace_back(std::type_index(typeid(bool)));
        mValidContainerElementTypes.emplace_back(std::type_index(typeid(char)));
        mValidContainerElementTypes.emplace_back(std::type_index(typeid(double)));
        mValidContainerElementTypes.emplace_back(std::type_index(typeid(float)));
        mValidContainerElementTypes.emplace_back(std::type_index(typeid(int)));
        mValidContainerElementTypes.emplace_back(std::type_index(typeid(std::string)));
    };
    ~DataWriter() = default;
    template<typename T> bool writeDataToFile(const std::string &filename, const std::vector<T> &data) {
        return mValidElementType(data) ? mWriteDataToFile(filename, data) : false;
    }
    template<typename T> bool writeDataToFile(const std::string &filename, const std::set<T> &data) {
        return mValidElementType(data) ? mWriteDataToFile(filename, data) : false;
    }
    template<typename T> bool writeDataToFile(const std::string &filename, const std::multiset<T> &data) {
        return mValidElementType(data) ? mWriteDataToFile(filename, data) : false;   
    }
private:
    template<template<class ...> class TContainerType, class TElementType> 
    bool mWriteDataToFile(const std::string &filename, const TContainerType<TElementType> &data) {
        if (data.empty()) {
            std::cerr << "[ERROR][DataWriter] - Data is empty. Skip writting data to file.\n";
            return false;
        }
        if (filename.empty()) {
            std::cerr << "[ERROR][DataWriter] - Filename is empty. Skip writting data to file.\n";
            return false;
        }
        std::ofstream outputFile(filename);
        if (!outputFile) {
            std::cerr << "[ERROR][DataWriter] - Can't open \"" << filename << "\" file. Skip writting data to file.\n";
            return false;
        }
        for (const auto &element : data) {
            outputFile << element;
        }
        outputFile.close();
        return true;
    }
    template<class T> bool mValidElementType(const T &container) {
        if (std::find(mValidContainerElementTypes.begin(), mValidContainerElementTypes.end(), 
                      typeid(*container.begin())) != mValidContainerElementTypes.end()) {
            return true;
        }
        std::cerr << "[ERROR][DataWriter] - Given container has invalid element type! \n";
        return false;
    }
private:
    std::vector<std::type_index> mValidContainerElementTypes;
};
 
} // fle_srtr namespace.