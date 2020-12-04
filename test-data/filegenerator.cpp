#include "filegenerator.h"
#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    if (argc < 2) {
        std::cout << "No filename passed as the first argument. Exit programm." << std::endl;
        return 1;
    }
    if (argc < 3) {
        std::cout << "No file size (in bytes) passed as the second argument. Exit programm." << std::endl;
        return 2;
    }
    std::string fileName {argv[1]};
    uint64_t size {std::strtoul(argv[2], nullptr, 10)};
    FileGenerator generator{};
    generator.generateRandomTextFile(fileName,size);
    return 0;
}
