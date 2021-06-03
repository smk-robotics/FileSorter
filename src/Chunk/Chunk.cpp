
#include "Chunk.h"

namespace file_sorter {

Chunk::Chunk(const std::string &filename) : mChunkFileName(filename) {}

void Chunk::createChunkFile() const {
    if (mChunkFileName.empty()) {
        std::cerr << "[ERROR]:[Chunk] - Skip creating chunk file. Filename is empty." << std::endl;
        return;
    }
    std::ofstream chunkFile(mChunkFileName);
    if (chunkFile.good()) {
        chunkFile.close();
    } else {
        std::cerr << "[ERROR]:[Chunk] - Can't create \"" << mChunkFileName << "\" chunk file." << std::endl;
    }
    return;
}

bool Chunk::deleteChunkFile() const {
    if (mChunkFileName.empty()) {
        std::cerr << "[ERROR]:[Chunk] - Skip deleting chunk file. Filename is empty." << std::endl;
        return false;
    }
    if (std::remove(mChunkFileName.c_str()) == 0) {
        return true;
    } else {
        std::cerr << "[ERROR]:[Chunk] - Can't delete \"" << mChunkFileName << "\" chunk file." << std::endl;
        return false;
    }
}

std::string Chunk::chunkFileName() const noexcept {
    return mChunkFileName;
}

void Chunk::setChunkFileName(const std::string &chunkFileName) noexcept {
    mChunkFileName = chunkFileName;
}

} // file_sorter namespace.