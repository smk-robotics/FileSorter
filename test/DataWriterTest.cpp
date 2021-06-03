#include <gtest/gtest.h>
#include <set>
#include <string>
#include <map>
#include "DataWriter.h"

class DataWriterTest : public ::testing::Test {
protected:
    file_sorter::DataWriter mDataWriter;
};

TEST_F(DataWriterTest, BasicConstructorTest) {
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::vector<char>{'x'}));
    ASSERT_FALSE(mDataWriter.writeDataToFile("/usr/DataWriterTest", std::vector<char>{'x'}));
    ASSERT_FALSE(mDataWriter.writeDataToFile("", std::vector<char>()));
    ASSERT_FALSE(mDataWriter.writeDataToFile("", std::vector<char>{'a', 'b', 'c'}));
}

TEST_F(DataWriterTest, VectorContainerTest) {
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::vector<bool>{true, false}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::vector<char>{'a', 'b', 'c'}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::vector<int>{0, 1, 2, 3, 4, 5}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::vector<float>{0.0f, 1.0f, 2.0f, 3.0f}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::vector<double>{0.0, 1.0, 2.0, 3.0, 4.0}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::vector<std::string>{"abc", "prc", "xyz"}));
}

TEST_F(DataWriterTest, SetContainerTest) {
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::set<bool>{true, false}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::set<char>{'a', 'b', 'c'}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::set<int>{0, 1, 2, 3, 4, 5}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::set<float>{0.0f, 1.0f, 2.0f, 3.0f}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::set<double>{0.0, 1.0, 2.0, 3.0, 4.0}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::set<std::string>{"abc", "prc", "xyz"}));
}

TEST_F(DataWriterTest, MultisetContainerTest) {
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::multiset<bool>{true, false}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::multiset<char>{'a', 'b', 'c'}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::multiset<int>{0, 1, 2, 3, 4, 5}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::multiset<float>{0.0f, 1.0f, 2.0f, 3.0f}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::multiset<double>{0.0, 1.0, 2.0, 3.0, 4.0}));
    ASSERT_TRUE(mDataWriter.writeDataToFile("/tmp/DataWriterTest", std::multiset<std::string>{"abc", "prc", "xyz"}));
}

// TEST_F(DataWriterTest, InvalidElementTypeTest) {
//     ASSERT_FALSE(mDataWriter.writeDataToFile("/tmp/DataWriterTest",
//                         std::vector<std::pair<bool, int>>{std::make_pair(true, 1), std::make_pair(false, 2)}));
// }

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}