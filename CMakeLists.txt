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
add_library(FileSplitter INTERFACE)

target_include_directories(FileSplitter INTERFACE
  include/FileSplitter
)

target_link_libraries(FileSplitter INTERFACE
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
