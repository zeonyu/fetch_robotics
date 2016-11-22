# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/zeon/catkin_ws/src/ros_infiniTAM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zeon/catkin_ws/src/ros_infiniTAM/build

# Include any dependencies generated for this target.
include src/Utils/CMakeFiles/Utils.dir/depend.make

# Include the progress variables for this target.
include src/Utils/CMakeFiles/Utils.dir/progress.make

# Include the compile flags for this target's objects.
include src/Utils/CMakeFiles/Utils.dir/flags.make

src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o: src/Utils/CMakeFiles/Utils.dir/flags.make
src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o: ../src/Utils/FileUtils.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zeon/catkin_ws/src/ros_infiniTAM/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o"
	cd /home/zeon/catkin_ws/src/ros_infiniTAM/build/src/Utils && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Utils.dir/FileUtils.cpp.o -c /home/zeon/catkin_ws/src/ros_infiniTAM/src/Utils/FileUtils.cpp

src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Utils.dir/FileUtils.cpp.i"
	cd /home/zeon/catkin_ws/src/ros_infiniTAM/build/src/Utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zeon/catkin_ws/src/ros_infiniTAM/src/Utils/FileUtils.cpp > CMakeFiles/Utils.dir/FileUtils.cpp.i

src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Utils.dir/FileUtils.cpp.s"
	cd /home/zeon/catkin_ws/src/ros_infiniTAM/build/src/Utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zeon/catkin_ws/src/ros_infiniTAM/src/Utils/FileUtils.cpp -o CMakeFiles/Utils.dir/FileUtils.cpp.s

src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.requires:
.PHONY : src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.requires

src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.provides: src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.requires
	$(MAKE) -f src/Utils/CMakeFiles/Utils.dir/build.make src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.provides.build
.PHONY : src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.provides

src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.provides.build: src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o

# Object files for target Utils
Utils_OBJECTS = \
"CMakeFiles/Utils.dir/FileUtils.cpp.o"

# External object files for target Utils
Utils_EXTERNAL_OBJECTS =

src/Utils/libUtils.so: src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o
src/Utils/libUtils.so: src/Utils/CMakeFiles/Utils.dir/build.make
src/Utils/libUtils.so: /usr/lib/x86_64-linux-gnu/libpng.so
src/Utils/libUtils.so: /usr/lib/x86_64-linux-gnu/libz.so
src/Utils/libUtils.so: src/Utils/CMakeFiles/Utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libUtils.so"
	cd /home/zeon/catkin_ws/src/ros_infiniTAM/build/src/Utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Utils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Utils/CMakeFiles/Utils.dir/build: src/Utils/libUtils.so
.PHONY : src/Utils/CMakeFiles/Utils.dir/build

src/Utils/CMakeFiles/Utils.dir/requires: src/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.requires
.PHONY : src/Utils/CMakeFiles/Utils.dir/requires

src/Utils/CMakeFiles/Utils.dir/clean:
	cd /home/zeon/catkin_ws/src/ros_infiniTAM/build/src/Utils && $(CMAKE_COMMAND) -P CMakeFiles/Utils.dir/cmake_clean.cmake
.PHONY : src/Utils/CMakeFiles/Utils.dir/clean

src/Utils/CMakeFiles/Utils.dir/depend:
	cd /home/zeon/catkin_ws/src/ros_infiniTAM/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zeon/catkin_ws/src/ros_infiniTAM /home/zeon/catkin_ws/src/ros_infiniTAM/src/Utils /home/zeon/catkin_ws/src/ros_infiniTAM/build /home/zeon/catkin_ws/src/ros_infiniTAM/build/src/Utils /home/zeon/catkin_ws/src/ros_infiniTAM/build/src/Utils/CMakeFiles/Utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Utils/CMakeFiles/Utils.dir/depend
