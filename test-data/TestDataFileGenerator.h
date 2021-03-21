#ifndef FILEGENERATOR_H
#define FILEGENERATOR_H

#include <fstream>

class FileGenerator {
public:
    static void generateRandomTextFile(std::string fileName, uint64_t fileSize) {
        std::ofstream dataFile;
        dataFile.open(fileName.c_str());
        if (!dataFile.good()) {
            std::cerr << "[ERROR] - Can't open file \"" << fileName << "\". Exit creating test data file." << std::endl;
            return;
        }
        uint64_t totalSizeSoFar = 0;
        uint64_t wordSize = 0;
        char letter;

        while(totalSizeSoFar < fileSize) {
            wordSize = 1 + rand()%14; // random word length
            while(totalSizeSoFar + wordSize > fileSize) {
                wordSize = 1 + rand()%14;
            }
            for(uint64_t j = 0; j < wordSize; j++) {
                letter = 'a' + rand()%26;
                dataFile << letter;
            }
            totalSizeSoFar += wordSize;
            if(totalSizeSoFar + 1 < fileSize) {
                dataFile << ' ';
                totalSizeSoFar++;
            }
        }
        dataFile.close();
    }
};

#endif // FILEGENERATOR_H
