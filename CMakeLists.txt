cmake_minimum_required(VERSION 3.10.0)
project(FileSorter VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)


set(CHUNK_LIBRARY "Chunk")
set(FILE_SPLITTER_LIBRARY "FileSplitter")
set(DATA_PROVIDER_LIBRARY "DataProvider")

include_directories(src)

###################
## CHUNK_LIBRARY ##
###################

file(GLOB CHUNK_LIBRARY_HEADERS CONFIGURE_DEPENDS src/${CHUNK_LIBRARY}/*.h)

add_library(${CHUNK_LIBRARY} INTERFACE)

target_include_directories(${CHUNK_LIBRARY} INTERFACE
    src/${CHUNK_LIBRARY}
 )
####################################
## DATA_PROVIDER_LIBRARY ##
####################################

file(GLOB DATA_PROVIDER_LIBRARY_HEADERS CONFIGURE_DEPENDS src/${DATA_PROVIDER_LIBRARY}/*.h)

add_library(${DATA_PROVIDER_LIBRARY} INTERFACE)

target_include_directories(${DATA_PROVIDER_LIBRARY} INTERFACE
    src/${DATA_PROVIDER_LIBRARY}
 )
######################
## SPLITTER_LIBRARY ##
######################

file(GLOB FILE_SPLITTER_LIBRARY_SOURCES CONFIGURE_DEPENDS src/${FILE_SPLITTER_LIBRARY}/*.cpp)
file(GLOB FILE_SPLITTER_LIBRARY_HEADERS CONFIGURE_DEPENDS src/${FILE_SPLITTER_LIBRARY}/*.h)

#add_library(${FILE_SPLITTER_LIBRARY} SHARED
#    ${FILE_SPLITTER_LIBRARY_SOURCES}
#    ${FILE_SPLITTER_LIBRARY_HEADERS}
#)

#target_link_libraries(${FILE_SPLITTER_LIBRARY}
#    ${CHUNK_LIBRARY}
#    ${MULTISET_DATA_PROVIDER_LIBRARY}
#)

################
## MAIN_BUILD ##
################

#add_executable(${PROJECT_NAME}
#    "src/main.cpp"
#)

#target_link_libraries(${PROJECT_NAME}
#    ${FILE_SPLITTER_LIBRARY}
#    ${MULTISET_DATA_PROVIDER_LIBRARY}
#)

#############
## TESTS ##
#############

set(GTEST_ROOT ${PROJECT_SOURCE_DIR}/third-party/out/lib)

find_package(GTest REQUIRED)

message("${PROJECT_NAME} - GTest library found -> ${GTEST_LIBRARIES}")

set(CHUNK_UNIT_TEST "MultisetChunkTest")
file(GLOB CHUNK_UNIT_TEST_SOURCES CONFIGURE_DEPENDS test/${CHUNK_UNIT_TEST}.cpp)
file(GLOB CHUNK_UNIT_TEST_HEADERS CONFIGURE_DEPENDS test/${CHUNK_UNIT_TEST}.h)

add_executable(${CHUNK_UNIT_TEST}
    ${CHUNK_UNIT_TEST_SOURCES}
    ${CHUNK_UNIT_TEST_HEADERS}
 )

target_link_libraries(${CHUNK_UNIT_TEST}
    ${CHUNK_LIBRARY}
    ${GTEST_LIBRARIES}
)

add_executable(MultisetDataProviderTest
    test/MultisetDataProviderTest.cpp
    ${CHUNK_UNIT_TEST_HEADERS}
)

target_link_libraries(MultisetDataProviderTest
    ${CHUNK_LIBRARY}
    ${DATA_PROVIDER_LIBRARY}
    ${GTEST_LIBRARIES}
)
