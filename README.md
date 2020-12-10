[![Build Status](https://travis-ci.com/smk-robotics/FileSorter.svg?branch=develop)](https://travis-ci.com/github/smk-robotics/FileSorter)

# FileSorter
External sorting for huge binary files.
 
## 1. Generate file with unsorted data for testing.
To generate file with usorted test data:
  - **Go to "test-data" folder.**
  - **Compile test data file generator:** </br>
    Simpliest way - use g++: `g++ fileGenerator.cpp -o fileGenerator`
  - **Run test data file generator:**</br> 
    Pass ***file name*** and ***file size in bytes*** in command line arguments: `fileGenerator {fileName} {fileSize}`. </br>
    For example to generate test data file with "TestDataFile" name and 1 Kb size run: `fileGenerator TestDataFile 1048576`
  
## 2. Run sorting algorithm.
To run sorting algorithm: </br>
  - **Go to FileSorter project git directory.** 
  - **Compile file sorter:** </br>
    Simpliest way - use g++: `g++ src/fileSorter.cpp -o fileSorter`.
  - **Run file sorter:** `fileSorter <UnsorteredDataFile> <SorteredDataFile>`. </br>
    **[WARNING]** Pass origin file (unsorted data) and result file (sorted data) names in command line arguments.

## 3. Use help.
Need help? Just pass **-h** or **--help** as command line argument: `fileSorter -h` or `fileSorter --help`.
