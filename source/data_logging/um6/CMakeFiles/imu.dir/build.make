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
include CMakeFiles/imu.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/imu.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/imu.dir/flags.make

CMakeFiles/imu.dir/src/imu.o: CMakeFiles/imu.dir/flags.make
CMakeFiles/imu.dir/src/imu.o: src/imu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/VictorLi/Gitdir/wombat/source/data_logging/um6/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/imu.dir/src/imu.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imu.dir/src/imu.o -c /Users/VictorLi/Gitdir/wombat/source/data_logging/um6/src/imu.cpp

CMakeFiles/imu.dir/src/imu.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imu.dir/src/imu.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/VictorLi/Gitdir/wombat/source/data_logging/um6/src/imu.cpp > CMakeFiles/imu.dir/src/imu.i

CMakeFiles/imu.dir/src/imu.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imu.dir/src/imu.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/VictorLi/Gitdir/wombat/source/data_logging/um6/src/imu.cpp -o CMakeFiles/imu.dir/src/imu.s

CMakeFiles/imu.dir/src/imu.o.requires:

.PHONY : CMakeFiles/imu.dir/src/imu.o.requires

CMakeFiles/imu.dir/src/imu.o.provides: CMakeFiles/imu.dir/src/imu.o.requires
	$(MAKE) -f CMakeFiles/imu.dir/build.make CMakeFiles/imu.dir/src/imu.o.provides.build
.PHONY : CMakeFiles/imu.dir/src/imu.o.provides

CMakeFiles/imu.dir/src/imu.o.provides.build: CMakeFiles/imu.dir/src/imu.o


# Object files for target imu
imu_OBJECTS = \
"CMakeFiles/imu.dir/src/imu.o"

# External object files for target imu
imu_EXTERNAL_OBJECTS =

imu: CMakeFiles/imu.dir/src/imu.o
imu: CMakeFiles/imu.dir/build.make
imu: libcomms.dylib
imu: libregisters.dylib
imu: CMakeFiles/imu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/VictorLi/Gitdir/wombat/source/data_logging/um6/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable imu"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/imu.dir/build: imu

.PHONY : CMakeFiles/imu.dir/build

CMakeFiles/imu.dir/requires: CMakeFiles/imu.dir/src/imu.o.requires

.PHONY : CMakeFiles/imu.dir/requires

CMakeFiles/imu.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/imu.dir/cmake_clean.cmake
.PHONY : CMakeFiles/imu.dir/clean

CMakeFiles/imu.dir/depend:
	cd /Users/VictorLi/Gitdir/wombat/source/data_logging/um6 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/VictorLi/Gitdir/wombat/source/data_logging/um6 /Users/VictorLi/Gitdir/wombat/source/data_logging/um6 /Users/VictorLi/Gitdir/wombat/source/data_logging/um6 /Users/VictorLi/Gitdir/wombat/source/data_logging/um6 /Users/VictorLi/Gitdir/wombat/source/data_logging/um6/CMakeFiles/imu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/imu.dir/depend

