# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /root/clion-2018.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /root/clion-2018.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/important/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/important/code/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ppt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ppt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ppt.dir/flags.make

CMakeFiles/ppt.dir/main.cpp.o: CMakeFiles/ppt.dir/flags.make
CMakeFiles/ppt.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/important/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ppt.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ppt.dir/main.cpp.o -c /root/important/code/main.cpp

CMakeFiles/ppt.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ppt.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/important/code/main.cpp > CMakeFiles/ppt.dir/main.cpp.i

CMakeFiles/ppt.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ppt.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/important/code/main.cpp -o CMakeFiles/ppt.dir/main.cpp.s

# Object files for target ppt
ppt_OBJECTS = \
"CMakeFiles/ppt.dir/main.cpp.o"

# External object files for target ppt
ppt_EXTERNAL_OBJECTS =

ppt: CMakeFiles/ppt.dir/main.cpp.o
ppt: CMakeFiles/ppt.dir/build.make
ppt: CMakeFiles/ppt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/important/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ppt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ppt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ppt.dir/build: ppt

.PHONY : CMakeFiles/ppt.dir/build

CMakeFiles/ppt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ppt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ppt.dir/clean

CMakeFiles/ppt.dir/depend:
	cd /root/important/code/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/important/code /root/important/code /root/important/code/cmake-build-debug /root/important/code/cmake-build-debug /root/important/code/cmake-build-debug/CMakeFiles/ppt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ppt.dir/depend
