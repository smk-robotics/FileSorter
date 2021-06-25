# Linking third party gtest, gmock and benchmark libraries.
set(GTEST_DIR ${PROJECT_SOURCE_DIR}/third-party/out/lib)
set(GTEST_ROOT ${PROJECT_SOURCE_DIR}/third-party/out/lib)
set(GTEST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third-party/out/include)
include_directories(${PROJECT_SOURCE_DIR}/third-party/out/include)

find_package(GTest REQUIRED)
# Checking, that used our gtest library (from third-party).
message("${PROJECT_NAME} - GTest library found -> ${GTEST_LIBRARIES}")

add_executable(ChunkTest
    ChunkTest.cpp
)

target_link_libraries(ChunkTest
    Chunk
    ${GTEST_LIBRARIES}
)

add_executable(MultisetDataProviderTest
    MultisetDataProviderTest.cpp
)

target_link_libraries(MultisetDataProviderTest
    Chunk
    DataProvider
    ${GTEST_LIBRARIES}
)

add_executable(DataSplitterTest
    DataSplitterTest.cpp
)

target_link_libraries(DataSplitterTest
    Chunk
    DataProvider
    DataSplitter
    ${GTEST_LIBRARIES}
)

add_executable(DataWriterTest
    DataWriterTest.cpp
)

target_link_libraries(DataWriterTest
    DataWriter
    ${GTEST_LIBRARIES}
)

add_executable(DataMergerTest
    DataMergerTest.cpp
)

target_link_libraries(DataMergerTest
    DataMerger
    ${GTEST_LIBRARIES}
)

################################
### TEST_DATA_FILE_GENERATOR ###
################################
add_executable(TestDataFileGenerator
  ../test-data/TestDataFileGenerator.cpp
  ../test-data/TestDataFileGenerator.h
)

gtest_discover_tests(ChunkTest)
gtest_discover_tests(MultisetDataProviderTest)
gtest_discover_tests(DataWriterTest)
gtest_discover_tests(DataSplitterTest)
gtest_discover_tests(DataMergerTest)
