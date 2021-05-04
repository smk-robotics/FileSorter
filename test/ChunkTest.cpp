#include <gtest/gtest.h>
#include <string_view>
#include <experimental/filesystem>
#include <fstream>
#include "Chunk.h"

constexpr std::string_view defaultChunkName = "defaultChunkName";

using namespace fle_srtr;

TEST(ChunkUnitTest, ConstructorTest) {
    Chunk chunk(static_cast<std::string>(defaultChunkName));
}

TEST(ChunkUnitTest, GettersSettersTest) {
    Chunk chunk(static_cast<std::string>(defaultChunkName));
    ASSERT_NO_THROW(chunk.chunkFileName());
    EXPECT_EQ(chunk.chunkFileName(), defaultChunkName);
    ASSERT_NO_THROW(chunk.setChunkFileName(static_cast<std::string>(defaultChunkName) + "Changed"));
    EXPECT_EQ(chunk.chunkFileName(), static_cast<std::string>(defaultChunkName) + "Changed");
}

TEST(ChunkUnitTest, CreateDeleteChunkFileTest) {
    Chunk chunk(static_cast<std::string>(defaultChunkName));
    EXPECT_FALSE(std::ifstream(static_cast<std::string>(defaultChunkName)));
    ASSERT_NO_THROW(chunk.createChunkFile());
    EXPECT_TRUE(std::ifstream(static_cast<std::string>(defaultChunkName)));
    ASSERT_NO_THROW(chunk.deleteChunkFile());
    EXPECT_FALSE(std::ifstream(static_cast<std::string>(defaultChunkName)));
}

TEST(ChunkUnitTest, WriteDataToChunkFileTest) {
    Chunk chunk(static_cast<std::string>(defaultChunkName));
    std::multiset<uint32_t> testSet;
    testSet.insert(1);
    testSet.insert(12);
    testSet.insert(3);
    testSet.insert(28);
    testSet.insert(84);
    ASSERT_NO_THROW(chunk.writeDataToChunkFile(testSet));
    EXPECT_TRUE(std::ifstream(static_cast<std::string>(defaultChunkName)));
    ASSERT_NO_THROW(chunk.deleteChunkFile());
    EXPECT_FALSE(std::ifstream(static_cast<std::string>(defaultChunkName)));
}

TEST(ChunkUnitTest, CreatChunkFileWithDataTest) {
    std::multiset<uint32_t> testSet;
    testSet.insert(1);
    testSet.insert(12);
    testSet.insert(3);
    testSet.insert(28);
    testSet.insert(84);
    Chunk chunk(static_cast<std::string>(defaultChunkName), testSet);
    ASSERT_NO_THROW(chunk.writeDataToChunkFile(testSet));
    EXPECT_TRUE(std::ifstream(static_cast<std::string>(defaultChunkName)));
    ASSERT_NO_THROW(chunk.deleteChunkFile());
    EXPECT_FALSE(std::ifstream(static_cast<std::string>(defaultChunkName)));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
