# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/build

# Include any dependencies generated for this target.
include CMakeFiles/RefragedContainer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RefragedContainer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RefragedContainer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RefragedContainer.dir/flags.make

CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.o: CMakeFiles/RefragedContainer.dir/flags.make
CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.o: /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/Container/RefragedContainer.cpp
CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.o: CMakeFiles/RefragedContainer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.o -MF CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.o.d -o CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.o -c /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/Container/RefragedContainer.cpp

CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/Container/RefragedContainer.cpp > CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.i

CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/Container/RefragedContainer.cpp -o CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.s

# Object files for target RefragedContainer
RefragedContainer_OBJECTS = \
"CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.o"

# External object files for target RefragedContainer
RefragedContainer_EXTERNAL_OBJECTS =

libs/libRefragedContainer.so: CMakeFiles/RefragedContainer.dir/Container/RefragedContainer.cpp.o
libs/libRefragedContainer.so: CMakeFiles/RefragedContainer.dir/build.make
libs/libRefragedContainer.so: CMakeFiles/RefragedContainer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libs/libRefragedContainer.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RefragedContainer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RefragedContainer.dir/build: libs/libRefragedContainer.so
.PHONY : CMakeFiles/RefragedContainer.dir/build

CMakeFiles/RefragedContainer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RefragedContainer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RefragedContainer.dir/clean

CMakeFiles/RefragedContainer.dir/depend:
	cd /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/build /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/build /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/build/CMakeFiles/RefragedContainer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/RefragedContainer.dir/depend

