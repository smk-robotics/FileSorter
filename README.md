[![Build Status](https://travis-ci.com/smk-robotics/FileSorter.svg?branch=develop)](https://travis-ci.com/github/smk-robotics/FileSorter)

# FileSorter
External sorting for binary files.


## Building library
  For separate library build just run:

  `cmake -DCMAKE_BUILD_TYPE=Release ..`

  `cmake --build . --target all`


## Building library with tests

1. Before build library with tests, build third-party gtest/gmock libraries first:

    ```cd third-party && ./build_third_party.sh```

2. Building library with test using cmake:

    `cmake -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=DEBUG ..`

    `cmake --build . --target all`

3. Generate data for tests:

    `./test/TestDataFileGenerator test-data/TestDataFile 5242880`

4. Run tests using ctest:

    `export GTEST_COLOR=1 && ctest --output-on-failure`


## License

  This software distributes under Creative Commons License.
