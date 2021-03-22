set(GTEST_DIR ${PROJECT_SOURCE_DIR}/third-party/out/lib)
set(GTEST_ROOT ${PROJECT_SOURCE_DIR}/third-party/out/lib)
set(GTEST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third-party/out/include)

find_package(GTest REQUIRED)

message("${PROJECT_NAME} - GTest library found -> ${GTEST_LIBRARIES}")

add_executable(MultisetChunkTest
    MultisetChunkTest.cpp
)

target_link_libraries(MultisetChunkTest
    Chunk
    ${GTEST_LIBRARIES}
)

add_executable(MultisetDataProviderTest
    MultisetDataProviderTest.cpp
    ${CHUNK_UNIT_TEST_HEADERS}
)

target_link_libraries(MultisetDataProviderTest
    Chunk
    DataProvider
    ${GTEST_LIBRARIES}
)

################################
### TEST_DATA_FILE_GENERATOR ###
################################
add_executable(TestDataFileGenerator
  ../test-data/TestDataFileGenerator.cpp
  ../test-data/TestDataFileGenerator.h
)

gtest_discover_tests(MultisetChunkTest)
gtest_discover_tests(MultisetDataProviderTest)
