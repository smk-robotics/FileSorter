#ifndef SIZESINGLETHREADSPLITTER_H
#define SIZESINGLETHREADSPLITTER_H
#include<vector>
#include "AbstractFileSplitter.h"
#include "Chunk/MultisetChunk.h"

template <class T> class SingleThreadBySizeSplitter : public AbstractFileSplitter<T> {
public:
    explicit SingleThreadBySizeSplitter(const uint16_t chunkSizeMb);
    std::vector<MultisetChunk> splitFileToChunks(const std::string &originFileName) override;
    ~SingleThreadBySizeSplitter() override = default;
private:
    /**
     * @brief Size of chunk in buffer counts.
     */
    uint32_t mChunkElementsNumberLimit;
};

#endif // SIZESINGLETHREADSPLITTER_H
