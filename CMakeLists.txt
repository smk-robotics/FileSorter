cmake_minimum_required(VERSION 3.10.0)
project(FileSorter LANGUAGES CXX VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Werror -Wall -Wextra -Wpedantic)
#################
## DATA_WRITER ##
#################
add_library(DataWriter INTERFACE)

target_include_directories(DataWriter INTERFACE
  include/DataWriter
)
#####################
### CHUNK_LIBRARY ###
#####################
add_library(Chunk SHARED
  src/Chunk/Chunk.cpp
)

target_include_directories(Chunk PUBLIC
  include/Chunk
)

target_link_libraries(Chunk PUBLIC
  DataWriter
)
#############################
### DATA_PROVIDER_LIBRARY ###
#############################
add_library(DataProvider INTERFACE)

target_include_directories(DataProvider INTERFACE
  include/DataProvider
)
######################
## SPLITTER_LIBRARY ##
######################
add_library(DataSplitter INTERFACE)

target_include_directories(DataSplitter INTERFACE
  include/DataSplitter
)

target_link_libraries(DataSplitter INTERFACE
   Chunk
)
######################
## MERGER_LIBRARY ##
######################
add_library(DataMerger INTERFACE)

target_include_directories(DataMerger INTERFACE
  include/DataMerger
)

target_link_libraries(DataMerger INTERFACE
   Chunk
)
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
if (BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()
