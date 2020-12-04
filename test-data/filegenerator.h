#ifndef FILEGENERATOR_H
#define FILEGENERATOR_H

#include <fstream>

class FileGenerator {
public:
    static void generateRandomTextFile(std::string fileName, uint64_t fileSize) {
        std::ofstream myfile;
        myfile.open(fileName.c_str());
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
                myfile << letter;
            }
            totalSizeSoFar += wordSize;
            if(totalSizeSoFar + 1 < fileSize) {
                myfile << ' ';
                totalSizeSoFar++;
            }
        }
        myfile.close();
    }
};

#endif // FILEGENERATOR_H
