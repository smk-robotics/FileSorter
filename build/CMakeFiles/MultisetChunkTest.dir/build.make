# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ksmirnov/local/Software_Patterns_Test/FileSorter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ksmirnov/local/Software_Patterns_Test/FileSorter/build

# Include any dependencies generated for this target.
include CMakeFiles/MultisetChunkTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MultisetChunkTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MultisetChunkTest.dir/flags.make

CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o: CMakeFiles/MultisetChunkTest.dir/flags.make
CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o: ../test/MultisetChunkTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ksmirnov/local/Software_Patterns_Test/FileSorter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o -c /home/ksmirnov/local/Software_Patterns_Test/FileSorter/test/MultisetChunkTest.cpp

CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ksmirnov/local/Software_Patterns_Test/FileSorter/test/MultisetChunkTest.cpp > CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.i

CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ksmirnov/local/Software_Patterns_Test/FileSorter/test/MultisetChunkTest.cpp -o CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.s

CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o.requires:

.PHONY : CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o.requires

CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o.provides: CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/MultisetChunkTest.dir/build.make CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o.provides.build
.PHONY : CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o.provides

CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o.provides.build: CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o


# Object files for target MultisetChunkTest
MultisetChunkTest_OBJECTS = \
"CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o"

# External object files for target MultisetChunkTest
MultisetChunkTest_EXTERNAL_OBJECTS =

MultisetChunkTest: CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o
MultisetChunkTest: CMakeFiles/MultisetChunkTest.dir/build.make
MultisetChunkTest: ../third-party/out/lib/libgtest.so
MultisetChunkTest: CMakeFiles/MultisetChunkTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ksmirnov/local/Software_Patterns_Test/FileSorter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MultisetChunkTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MultisetChunkTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MultisetChunkTest.dir/build: MultisetChunkTest

.PHONY : CMakeFiles/MultisetChunkTest.dir/build

CMakeFiles/MultisetChunkTest.dir/requires: CMakeFiles/MultisetChunkTest.dir/test/MultisetChunkTest.cpp.o.requires

.PHONY : CMakeFiles/MultisetChunkTest.dir/requires

CMakeFiles/MultisetChunkTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MultisetChunkTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MultisetChunkTest.dir/clean

CMakeFiles/MultisetChunkTest.dir/depend:
	cd /home/ksmirnov/local/Software_Patterns_Test/FileSorter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ksmirnov/local/Software_Patterns_Test/FileSorter /home/ksmirnov/local/Software_Patterns_Test/FileSorter /home/ksmirnov/local/Software_Patterns_Test/FileSorter/build /home/ksmirnov/local/Software_Patterns_Test/FileSorter/build /home/ksmirnov/local/Software_Patterns_Test/FileSorter/build/CMakeFiles/MultisetChunkTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MultisetChunkTest.dir/depend
