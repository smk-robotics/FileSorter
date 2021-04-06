#include <gtest/gtest.h>
#include "SingleThreadSizeSplitter.h"

class FileSplitterTest : public ::testing::Test {
public:
    void SetUp() {
        mTestDataFilename = __FILE__;
        mTestDataFilename = mTestDataFilename.substr(0, mTestDataFilename.rfind("test"));
        mTestDataFilename += "test-data/TestDataFile";
        if (!std::fstream(mTestDataFilename.c_str())) {
            throw std::runtime_error("Error while opening test data file - " + mTestDataFilename);
        }
    }
protected:
    std::string mTestDataFilename;
};

TEST_F(FileSplitterTest, BasicConstructorTest) {
    SingleThreadSizeSplitter<uint32_t> fileSplitter(1);
}

TEST_F(FileSplitterTest, SplitFileTo1MbTest) {
    SingleThreadSizeSplitter<uint32_t> fileSplitter(2);
    std::vector<MultisetChunk<uint32_t>> chunks;
    EXPECT_NO_THROW(chunks = fileSplitter.splitFileToChunks(mTestDataFilename));
    EXPECT_EQ(chunks.size(), 3);
    for (const auto &chunk : chunks) {
        EXPECT_NO_THROW(chunk.deleteChunkFile());
    }
}

TEST_F(FileSplitterTest, SplitFileTo6MbTest) {
    SingleThreadSizeSplitter<uint32_t> fileSplitter(6);
    std::vector<MultisetChunk<uint32_t>> chunks;
    EXPECT_NO_THROW(chunks = fileSplitter.splitFileToChunks(mTestDataFilename));
    EXPECT_EQ(chunks.size(), 1);
    for (const auto &chunk : chunks) {
        EXPECT_NO_THROW(chunk.deleteChunkFile());
    }
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}