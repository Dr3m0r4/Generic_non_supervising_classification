# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/dr3m/Travaux/Cimg_generic/Current_version

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dr3m/Travaux/Cimg_generic/Current_version/build

# Include any dependencies generated for this target.
include CMakeFiles/project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project.dir/flags.make

CMakeFiles/project.dir/src/main.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dr3m/Travaux/Cimg_generic/Current_version/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/project.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/src/main.cpp.o -c /home/dr3m/Travaux/Cimg_generic/Current_version/src/main.cpp

CMakeFiles/project.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dr3m/Travaux/Cimg_generic/Current_version/src/main.cpp > CMakeFiles/project.dir/src/main.cpp.i

CMakeFiles/project.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dr3m/Travaux/Cimg_generic/Current_version/src/main.cpp -o CMakeFiles/project.dir/src/main.cpp.s

CMakeFiles/project.dir/src/ML.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/src/ML.cpp.o: ../src/ML.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dr3m/Travaux/Cimg_generic/Current_version/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/project.dir/src/ML.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project.dir/src/ML.cpp.o -c /home/dr3m/Travaux/Cimg_generic/Current_version/src/ML.cpp

CMakeFiles/project.dir/src/ML.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/src/ML.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dr3m/Travaux/Cimg_generic/Current_version/src/ML.cpp > CMakeFiles/project.dir/src/ML.cpp.i

CMakeFiles/project.dir/src/ML.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/src/ML.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dr3m/Travaux/Cimg_generic/Current_version/src/ML.cpp -o CMakeFiles/project.dir/src/ML.cpp.s

# Object files for target project
project_OBJECTS = \
"CMakeFiles/project.dir/src/main.cpp.o" \
"CMakeFiles/project.dir/src/ML.cpp.o"

# External object files for target project
project_EXTERNAL_OBJECTS =

project: CMakeFiles/project.dir/src/main.cpp.o
project: CMakeFiles/project.dir/src/ML.cpp.o
project: CMakeFiles/project.dir/build.make
project: CMakeFiles/project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dr3m/Travaux/Cimg_generic/Current_version/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project.dir/build: project

.PHONY : CMakeFiles/project.dir/build

CMakeFiles/project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/project.dir/clean

CMakeFiles/project.dir/depend:
	cd /home/dr3m/Travaux/Cimg_generic/Current_version/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dr3m/Travaux/Cimg_generic/Current_version /home/dr3m/Travaux/Cimg_generic/Current_version /home/dr3m/Travaux/Cimg_generic/Current_version/build /home/dr3m/Travaux/Cimg_generic/Current_version/build /home/dr3m/Travaux/Cimg_generic/Current_version/build/CMakeFiles/project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/project.dir/depend

