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
CMAKE_SOURCE_DIR = /home/kali/git

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kali/git/build

# Include any dependencies generated for this target.
include CMakeFiles/FragileContainer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/FragileContainer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/FragileContainer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FragileContainer.dir/flags.make

CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.o: CMakeFiles/FragileContainer.dir/flags.make
CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.o: /home/kali/git/Container/FragileContainer.cpp
CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.o: CMakeFiles/FragileContainer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kali/git/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.o -MF CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.o.d -o CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.o -c /home/kali/git/Container/FragileContainer.cpp

CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/git/Container/FragileContainer.cpp > CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.i

CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/git/Container/FragileContainer.cpp -o CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.s

# Object files for target FragileContainer
FragileContainer_OBJECTS = \
"CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.o"

# External object files for target FragileContainer
FragileContainer_EXTERNAL_OBJECTS =

libs/libFragileContainer.so: CMakeFiles/FragileContainer.dir/Container/FragileContainer.cpp.o
libs/libFragileContainer.so: CMakeFiles/FragileContainer.dir/build.make
libs/libFragileContainer.so: CMakeFiles/FragileContainer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/kali/git/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libs/libFragileContainer.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FragileContainer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FragileContainer.dir/build: libs/libFragileContainer.so
.PHONY : CMakeFiles/FragileContainer.dir/build

CMakeFiles/FragileContainer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FragileContainer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FragileContainer.dir/clean

CMakeFiles/FragileContainer.dir/depend:
	cd /home/kali/git/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kali/git /home/kali/git /home/kali/git/build /home/kali/git/build /home/kali/git/build/CMakeFiles/FragileContainer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/FragileContainer.dir/depend

