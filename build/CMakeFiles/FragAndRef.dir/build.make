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
include CMakeFiles/FragAndRef.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/FragAndRef.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/FragAndRef.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FragAndRef.dir/flags.make

CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.o: CMakeFiles/FragAndRef.dir/flags.make
CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.o: /home/kali/git/Container/Frag_and_Ref.cpp
CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.o: CMakeFiles/FragAndRef.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kali/git/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.o -MF CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.o.d -o CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.o -c /home/kali/git/Container/Frag_and_Ref.cpp

CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/git/Container/Frag_and_Ref.cpp > CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.i

CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/git/Container/Frag_and_Ref.cpp -o CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.s

# Object files for target FragAndRef
FragAndRef_OBJECTS = \
"CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.o"

# External object files for target FragAndRef
FragAndRef_EXTERNAL_OBJECTS =

libs/libFragAndRef.so: CMakeFiles/FragAndRef.dir/Container/Frag_and_Ref.cpp.o
libs/libFragAndRef.so: CMakeFiles/FragAndRef.dir/build.make
libs/libFragAndRef.so: CMakeFiles/FragAndRef.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/kali/git/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libs/libFragAndRef.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FragAndRef.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FragAndRef.dir/build: libs/libFragAndRef.so
.PHONY : CMakeFiles/FragAndRef.dir/build

CMakeFiles/FragAndRef.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FragAndRef.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FragAndRef.dir/clean

CMakeFiles/FragAndRef.dir/depend:
	cd /home/kali/git/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kali/git /home/kali/git /home/kali/git/build /home/kali/git/build /home/kali/git/build/CMakeFiles/FragAndRef.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/FragAndRef.dir/depend

