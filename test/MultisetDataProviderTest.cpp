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

TEST_F(MultisetDataProviderTest, MultisetDataProviderConstructorTest) {
   MultisetDataProvider<uint32_t> multisetDataProvider(mTestDataFilename, 100);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
