#include <string>
#include "Chunk/Chunk.h"

#pragma once

template <class T> class AbstractFileSplitter {
public:
    virtual std::vector<Chunk<T>> splitFileToChunks(const std::string &originFileName) = 0;
    virtual ~AbstractFileSplitter() = default;
};
