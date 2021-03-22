#include <iostream>
#include "TestDataFileGenerator.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    if (argc < 2) {
        std::cerr << "[ERROR] - No filename passed as the first argument. Exit program." << std::endl;
        return 1;
    }
    if (argc < 3) {
        std::cerr << "[ERROR] - No file size (in bytes) passed as the second argument. Exit program." << std::endl;
        return 2;
    }
    std::string givenFilename {argv[1]};
    uint64_t size {std::strtoul(argv[2], nullptr, 10)};
    std::string testDataFilename = __FILE__;
    testDataFilename = testDataFilename.substr(0, testDataFilename.rfind("test"));
    testDataFilename += givenFilename;
    FileGenerator generator{};
    generator.generateRandomTextFile(testDataFilename, size);
    return 0;
}
