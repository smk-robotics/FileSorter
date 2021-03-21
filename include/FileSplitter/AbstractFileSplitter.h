#ifndef FILESPLITTERINTERFACE_H
#define FILESPLITTERINTERFACE_H
#include <string>
#include "Chunk/Chunk.h"

template <class T> class AbstractFileSplitter {
public:
    virtual std::vector<Chunk<T>> splitFileToChunks(const std::string &originFileName) = 0;
    virtual ~AbstractFileSplitter() = default;
};

#endif // FILESPLITTERINTERFACE_H
