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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/VictorLi/Gitdir/wombat/source/data_logging/um6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/VictorLi/Gitdir/wombat/source/data_logging/um6

# Include any dependencies generated for this target.
include CMakeFiles/comms.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/comms.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/comms.dir/flags.make

CMakeFiles/comms.dir/src/comms.o: CMakeFiles/comms.dir/flags.make
CMakeFiles/comms.dir/src/comms.o: src/comms.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/VictorLi/Gitdir/wombat/source/data_logging/um6/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/comms.dir/src/comms.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/comms.dir/src/comms.o -c /Users/VictorLi/Gitdir/wombat/source/data_logging/um6/src/comms.cpp

CMakeFiles/comms.dir/src/comms.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comms.dir/src/comms.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/VictorLi/Gitdir/wombat/source/data_logging/um6/src/comms.cpp > CMakeFiles/comms.dir/src/comms.i

CMakeFiles/comms.dir/src/comms.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comms.dir/src/comms.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/VictorLi/Gitdir/wombat/source/data_logging/um6/src/comms.cpp -o CMakeFiles/comms.dir/src/comms.s

CMakeFiles/comms.dir/src/comms.o.requires:

.PHONY : CMakeFiles/comms.dir/src/comms.o.requires

CMakeFiles/comms.dir/src/comms.o.provides: CMakeFiles/comms.dir/src/comms.o.requires
	$(MAKE) -f CMakeFiles/comms.dir/build.make CMakeFiles/comms.dir/src/comms.o.provides.build
.PHONY : CMakeFiles/comms.dir/src/comms.o.provides

CMakeFiles/comms.dir/src/comms.o.provides.build: CMakeFiles/comms.dir/src/comms.o


# Object files for target comms
comms_OBJECTS = \
"CMakeFiles/comms.dir/src/comms.o"

# External object files for target comms
comms_EXTERNAL_OBJECTS =

libcomms.dylib: CMakeFiles/comms.dir/src/comms.o
libcomms.dylib: CMakeFiles/comms.dir/build.make
libcomms.dylib: CMakeFiles/comms.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/VictorLi/Gitdir/wombat/source/data_logging/um6/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libcomms.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/comms.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/comms.dir/build: libcomms.dylib

.PHONY : CMakeFiles/comms.dir/build

CMakeFiles/comms.dir/requires: CMakeFiles/comms.dir/src/comms.o.requires

.PHONY : CMakeFiles/comms.dir/requires

CMakeFiles/comms.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/comms.dir/cmake_clean.cmake
.PHONY : CMakeFiles/comms.dir/clean

CMakeFiles/comms.dir/depend:
	cd /Users/VictorLi/Gitdir/wombat/source/data_logging/um6 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/VictorLi/Gitdir/wombat/source/data_logging/um6 /Users/VictorLi/Gitdir/wombat/source/data_logging/um6 /Users/VictorLi/Gitdir/wombat/source/data_logging/um6 /Users/VictorLi/Gitdir/wombat/source/data_logging/um6 /Users/VictorLi/Gitdir/wombat/source/data_logging/um6/CMakeFiles/comms.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/comms.dir/depend

