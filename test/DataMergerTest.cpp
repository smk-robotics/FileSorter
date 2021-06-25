#include <gtest/gtest.h>
#include <MergeSorter.h>

using namespace file_sorter;

TEST(DataMergerTest, ConstructorTest) {
    MergeSorter mergeSorter();
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}