# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/mario/Documents/clion-2017.1.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/mario/Documents/clion-2017.1.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mario/CLionProjects/DBCli

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mario/CLionProjects/DBCli/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DBCli.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DBCli.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DBCli.dir/flags.make

CMakeFiles/DBCli.dir/main.cpp.o: CMakeFiles/DBCli.dir/flags.make
CMakeFiles/DBCli.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mario/CLionProjects/DBCli/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DBCli.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBCli.dir/main.cpp.o -c /home/mario/CLionProjects/DBCli/main.cpp

CMakeFiles/DBCli.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBCli.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mario/CLionProjects/DBCli/main.cpp > CMakeFiles/DBCli.dir/main.cpp.i

CMakeFiles/DBCli.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBCli.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mario/CLionProjects/DBCli/main.cpp -o CMakeFiles/DBCli.dir/main.cpp.s

CMakeFiles/DBCli.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/DBCli.dir/main.cpp.o.requires

CMakeFiles/DBCli.dir/main.cpp.o.provides: CMakeFiles/DBCli.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBCli.dir/build.make CMakeFiles/DBCli.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/DBCli.dir/main.cpp.o.provides

CMakeFiles/DBCli.dir/main.cpp.o.provides.build: CMakeFiles/DBCli.dir/main.cpp.o


CMakeFiles/DBCli.dir/DbConsole.cpp.o: CMakeFiles/DBCli.dir/flags.make
CMakeFiles/DBCli.dir/DbConsole.cpp.o: ../DbConsole.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mario/CLionProjects/DBCli/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DBCli.dir/DbConsole.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBCli.dir/DbConsole.cpp.o -c /home/mario/CLionProjects/DBCli/DbConsole.cpp

CMakeFiles/DBCli.dir/DbConsole.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBCli.dir/DbConsole.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mario/CLionProjects/DBCli/DbConsole.cpp > CMakeFiles/DBCli.dir/DbConsole.cpp.i

CMakeFiles/DBCli.dir/DbConsole.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBCli.dir/DbConsole.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mario/CLionProjects/DBCli/DbConsole.cpp -o CMakeFiles/DBCli.dir/DbConsole.cpp.s

CMakeFiles/DBCli.dir/DbConsole.cpp.o.requires:

.PHONY : CMakeFiles/DBCli.dir/DbConsole.cpp.o.requires

CMakeFiles/DBCli.dir/DbConsole.cpp.o.provides: CMakeFiles/DBCli.dir/DbConsole.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBCli.dir/build.make CMakeFiles/DBCli.dir/DbConsole.cpp.o.provides.build
.PHONY : CMakeFiles/DBCli.dir/DbConsole.cpp.o.provides

CMakeFiles/DBCli.dir/DbConsole.cpp.o.provides.build: CMakeFiles/DBCli.dir/DbConsole.cpp.o


# Object files for target DBCli
DBCli_OBJECTS = \
"CMakeFiles/DBCli.dir/main.cpp.o" \
"CMakeFiles/DBCli.dir/DbConsole.cpp.o"

# External object files for target DBCli
DBCli_EXTERNAL_OBJECTS =

DBCli: CMakeFiles/DBCli.dir/main.cpp.o
DBCli: CMakeFiles/DBCli.dir/DbConsole.cpp.o
DBCli: CMakeFiles/DBCli.dir/build.make
DBCli: CMakeFiles/DBCli.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mario/CLionProjects/DBCli/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable DBCli"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DBCli.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DBCli.dir/build: DBCli

.PHONY : CMakeFiles/DBCli.dir/build

CMakeFiles/DBCli.dir/requires: CMakeFiles/DBCli.dir/main.cpp.o.requires
CMakeFiles/DBCli.dir/requires: CMakeFiles/DBCli.dir/DbConsole.cpp.o.requires

.PHONY : CMakeFiles/DBCli.dir/requires

CMakeFiles/DBCli.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DBCli.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DBCli.dir/clean

CMakeFiles/DBCli.dir/depend:
	cd /home/mario/CLionProjects/DBCli/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mario/CLionProjects/DBCli /home/mario/CLionProjects/DBCli /home/mario/CLionProjects/DBCli/cmake-build-debug /home/mario/CLionProjects/DBCli/cmake-build-debug /home/mario/CLionProjects/DBCli/cmake-build-debug/CMakeFiles/DBCli.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DBCli.dir/depend
