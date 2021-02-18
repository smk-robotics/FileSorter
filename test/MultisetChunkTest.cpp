#include <gtest/gtest.h>
#include <string_view>
#include <experimental/filesystem>
#include <fstream>
#include "Chunk/MultisetChunk.h"

constexpr std::string_view defaultChunkName = "defaultChunkName";

TEST(MultisetChunkUnitTest, ConstructorTest) {
    MultisetChunk<int> intMultisetChunk(static_cast<std::string>(defaultChunkName));
    MultisetChunk<uint32_t> uintMultisetChunk(static_cast<std::string>(defaultChunkName));
    MultisetChunk<float> floatMultisetChunk(static_cast<std::string>(defaultChunkName));
    MultisetChunk<double> doubleMultisetChunk(static_cast<std::string>(defaultChunkName));
    MultisetChunk<std::string> stringMultisetChunk(static_cast<std::string>(defaultChunkName));
}

TEST(MultisetChunkUnitTest, GettersSettersTest) {
    MultisetChunk<uint32_t> multisetChunk(static_cast<std::string>(defaultChunkName));
    ASSERT_NO_THROW(multisetChunk.chunkFileName());
    EXPECT_EQ(multisetChunk.chunkFileName(), defaultChunkName);
    ASSERT_NO_THROW(multisetChunk.setChunkFileName(static_cast<std::string>(defaultChunkName) + "Changed"));
    EXPECT_EQ(multisetChunk.chunkFileName(), static_cast<std::string>(defaultChunkName) + "Changed");
}

TEST(MultisetChunkUnitTest, CreateDeleteChunkFileTest) {
    MultisetChunk<uint32_t> multisetChunk(static_cast<std::string>(defaultChunkName));
    EXPECT_FALSE(std::ifstream(static_cast<std::string>(defaultChunkName)));
    ASSERT_NO_THROW(multisetChunk.createChunkFile());
    EXPECT_TRUE(std::ifstream(static_cast<std::string>(defaultChunkName)));
    ASSERT_NO_THROW(multisetChunk.deleteChunkFile());
    EXPECT_FALSE(std::ifstream(static_cast<std::string>(defaultChunkName)));
}

TEST(MultisetChunkUnitTest, WriteDataToChunkFileTest) {
    MultisetChunk<uint32_t> multisetChunk(static_cast<std::string>(defaultChunkName));
    std::multiset<uint32_t> testSet;
    testSet.insert(1);
    testSet.insert(12);
    testSet.insert(3);
    testSet.insert(28);
    testSet.insert(84);
    ASSERT_NO_THROW(multisetChunk.writeDataToChunkFile(testSet));
    EXPECT_TRUE(std::ifstream(static_cast<std::string>(defaultChunkName)));
    ASSERT_NO_THROW(multisetChunk.deleteChunkFile());
    EXPECT_FALSE(std::ifstream(static_cast<std::string>(defaultChunkName)));
}

TEST(MultisetChunkUnitTest, CreatChunkFileWithDataTest) {
    std::multiset<uint32_t> testSet;
    testSet.insert(1);
    testSet.insert(12);
    testSet.insert(3);
    testSet.insert(28);
    testSet.insert(84);
    MultisetChunk<uint32_t> multisetChunk(static_cast<std::string>(defaultChunkName), testSet);
    ASSERT_NO_THROW(multisetChunk.writeDataToChunkFile(testSet));
    EXPECT_TRUE(std::ifstream(static_cast<std::string>(defaultChunkName)));
    ASSERT_NO_THROW(multisetChunk.deleteChunkFile());
    EXPECT_FALSE(std::ifstream(static_cast<std::string>(defaultChunkName)));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
