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
include CMakeFiles/AnimalContainer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/AnimalContainer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/AnimalContainer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AnimalContainer.dir/flags.make

CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.o: CMakeFiles/AnimalContainer.dir/flags.make
CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.o: /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/Container/AnimalContainer.cpp
CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.o: CMakeFiles/AnimalContainer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.o -MF CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.o.d -o CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.o -c /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/Container/AnimalContainer.cpp

CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/Container/AnimalContainer.cpp > CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.i

CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/Container/AnimalContainer.cpp -o CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.s

# Object files for target AnimalContainer
AnimalContainer_OBJECTS = \
"CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.o"

# External object files for target AnimalContainer
AnimalContainer_EXTERNAL_OBJECTS =

libs/libAnimalContainer.so: CMakeFiles/AnimalContainer.dir/Container/AnimalContainer.cpp.o
libs/libAnimalContainer.so: CMakeFiles/AnimalContainer.dir/build.make
libs/libAnimalContainer.so: CMakeFiles/AnimalContainer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libs/libAnimalContainer.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AnimalContainer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AnimalContainer.dir/build: libs/libAnimalContainer.so
.PHONY : CMakeFiles/AnimalContainer.dir/build

CMakeFiles/AnimalContainer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AnimalContainer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AnimalContainer.dir/clean

CMakeFiles/AnimalContainer.dir/depend:
	cd /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/build /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/build /home/kali/Labs/Lab3OOP-delitel/Lab3OOP-delitel/build/CMakeFiles/AnimalContainer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/AnimalContainer.dir/depend

