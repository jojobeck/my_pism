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


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /p/system/packages/cmake/3.10.2/bin/cmake

# The command to remove a file.
RM = /p/system/packages/cmake/3.10.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/beckmann/pism/build/CMakeFiles/CMakeTmp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/beckmann/pism/build/CMakeFiles/CMakeTmp

# Include any dependencies generated for this target.
include CMakeFiles/cmTC_4812e.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cmTC_4812e.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmTC_4812e.dir/flags.make

CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o: CMakeFiles/cmTC_4812e.dir/flags.make
CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o: testCCompiler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/beckmann/pism/build/CMakeFiles/CMakeTmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o"
	/p/system/packages/intel/parallel_studio_xe_2018_update1/compilers_and_libraries_2018.1.163/linux/mpi/intel64/bin/mpiicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o   -c /home/beckmann/pism/build/CMakeFiles/CMakeTmp/testCCompiler.c

CMakeFiles/cmTC_4812e.dir/testCCompiler.c.i: cmake_force
	@echo "Preprocessing C source to CMakeFiles/cmTC_4812e.dir/testCCompiler.c.i"
	/p/system/packages/intel/parallel_studio_xe_2018_update1/compilers_and_libraries_2018.1.163/linux/mpi/intel64/bin/mpiicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/beckmann/pism/build/CMakeFiles/CMakeTmp/testCCompiler.c > CMakeFiles/cmTC_4812e.dir/testCCompiler.c.i

CMakeFiles/cmTC_4812e.dir/testCCompiler.c.s: cmake_force
	@echo "Compiling C source to assembly CMakeFiles/cmTC_4812e.dir/testCCompiler.c.s"
	/p/system/packages/intel/parallel_studio_xe_2018_update1/compilers_and_libraries_2018.1.163/linux/mpi/intel64/bin/mpiicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/beckmann/pism/build/CMakeFiles/CMakeTmp/testCCompiler.c -o CMakeFiles/cmTC_4812e.dir/testCCompiler.c.s

CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o.requires:

.PHONY : CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o.requires

CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o.provides: CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o.requires
	$(MAKE) -f CMakeFiles/cmTC_4812e.dir/build.make CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o.provides.build
.PHONY : CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o.provides

CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o.provides.build: CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o


# Object files for target cmTC_4812e
cmTC_4812e_OBJECTS = \
"CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o"

# External object files for target cmTC_4812e
cmTC_4812e_EXTERNAL_OBJECTS =

cmTC_4812e: CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o
cmTC_4812e: CMakeFiles/cmTC_4812e.dir/build.make
cmTC_4812e: CMakeFiles/cmTC_4812e.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/beckmann/pism/build/CMakeFiles/CMakeTmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cmTC_4812e"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmTC_4812e.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmTC_4812e.dir/build: cmTC_4812e

.PHONY : CMakeFiles/cmTC_4812e.dir/build

CMakeFiles/cmTC_4812e.dir/requires: CMakeFiles/cmTC_4812e.dir/testCCompiler.c.o.requires

.PHONY : CMakeFiles/cmTC_4812e.dir/requires

CMakeFiles/cmTC_4812e.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cmTC_4812e.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cmTC_4812e.dir/clean

CMakeFiles/cmTC_4812e.dir/depend:
	cd /home/beckmann/pism/build/CMakeFiles/CMakeTmp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/beckmann/pism/build/CMakeFiles/CMakeTmp /home/beckmann/pism/build/CMakeFiles/CMakeTmp /home/beckmann/pism/build/CMakeFiles/CMakeTmp /home/beckmann/pism/build/CMakeFiles/CMakeTmp /home/beckmann/pism/build/CMakeFiles/CMakeTmp/CMakeFiles/cmTC_4812e.dir/DependInfo.cmake
.PHONY : CMakeFiles/cmTC_4812e.dir/depend

