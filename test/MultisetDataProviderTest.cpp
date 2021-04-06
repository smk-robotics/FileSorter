#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <gtest/gtest.h>
#include "MultisetDataProvider.h"

class MultisetDataProviderTest : public ::testing::Test {
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

TEST_F(MultisetDataProviderTest, ConstructorTest) {
    MultisetDataProvider<uint32_t> multisetDataProvider(mTestDataFilename, 100);
    [[maybe_unused]] AbstractFileDataProvider<uint32_t, std::multiset> &dataProvider = multisetDataProvider;
}

TEST_F(MultisetDataProviderTest, BasicFunctionsTest) {
   MultisetDataProvider<uint32_t> multisetDataProvider(mTestDataFilename, 100);
   EXPECT_EQ(multisetDataProvider.currentCharacterPosition(), 0);
   EXPECT_EQ(multisetDataProvider.getFileSize(), 5242880);
   EXPECT_EQ(multisetDataProvider.fileName(), mTestDataFilename);
   EXPECT_EQ(multisetDataProvider.currentCharacterPosition(), 0);
   EXPECT_EQ(multisetDataProvider.finish(), false);
}

TEST_F(MultisetDataProviderTest, DataReaderFunctionTest) {
   MultisetDataProvider<uint32_t> multisetDataProvider(mTestDataFilename, 1000);
   std::multiset<uint32_t> data;
   EXPECT_NO_THROW(data = multisetDataProvider.GetDataFromFile());
   EXPECT_EQ(data.size(), 1000);
   EXPECT_FALSE(multisetDataProvider.finish());
   while (!multisetDataProvider.finish()) {
       EXPECT_NO_THROW(data = multisetDataProvider.GetDataFromFile());
   }
   EXPECT_EQ(multisetDataProvider.currentCharacterPosition(), 5242880);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
