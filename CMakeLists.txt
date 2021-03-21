cmake_minimum_required(VERSION 3.10.0)
project(FileSorter VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall)

set(FILE_SPLITTER_LIBRARY "FileSplitter")
#####################
### CHUNK_LIBRARY ###
#####################
add_library(Chunk INTERFACE)

target_include_directories(Chunk INTERFACE
    include/Chunk
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
if (BUILD_TESTS) 
  enable_testing()
  add_subdirectory(test)
endif()