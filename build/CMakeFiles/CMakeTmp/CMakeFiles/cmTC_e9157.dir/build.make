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
include CMakeFiles/cmTC_e9157.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cmTC_e9157.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmTC_e9157.dir/flags.make

CMakeFiles/cmTC_e9157.dir/src.c.o: CMakeFiles/cmTC_e9157.dir/flags.make
CMakeFiles/cmTC_e9157.dir/src.c.o: src.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/beckmann/pism/build/CMakeFiles/CMakeTmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cmTC_e9157.dir/src.c.o"
	/p/system/packages/intel/parallel_studio_xe_2018_update1/compilers_and_libraries_2018.1.163/linux/mpi/intel64/bin/mpiicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cmTC_e9157.dir/src.c.o   -c /home/beckmann/pism/build/CMakeFiles/CMakeTmp/src.c

CMakeFiles/cmTC_e9157.dir/src.c.i: cmake_force
	@echo "Preprocessing C source to CMakeFiles/cmTC_e9157.dir/src.c.i"
	/p/system/packages/intel/parallel_studio_xe_2018_update1/compilers_and_libraries_2018.1.163/linux/mpi/intel64/bin/mpiicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/beckmann/pism/build/CMakeFiles/CMakeTmp/src.c > CMakeFiles/cmTC_e9157.dir/src.c.i

CMakeFiles/cmTC_e9157.dir/src.c.s: cmake_force
	@echo "Compiling C source to assembly CMakeFiles/cmTC_e9157.dir/src.c.s"
	/p/system/packages/intel/parallel_studio_xe_2018_update1/compilers_and_libraries_2018.1.163/linux/mpi/intel64/bin/mpiicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/beckmann/pism/build/CMakeFiles/CMakeTmp/src.c -o CMakeFiles/cmTC_e9157.dir/src.c.s

CMakeFiles/cmTC_e9157.dir/src.c.o.requires:

.PHONY : CMakeFiles/cmTC_e9157.dir/src.c.o.requires

CMakeFiles/cmTC_e9157.dir/src.c.o.provides: CMakeFiles/cmTC_e9157.dir/src.c.o.requires
	$(MAKE) -f CMakeFiles/cmTC_e9157.dir/build.make CMakeFiles/cmTC_e9157.dir/src.c.o.provides.build
.PHONY : CMakeFiles/cmTC_e9157.dir/src.c.o.provides

CMakeFiles/cmTC_e9157.dir/src.c.o.provides.build: CMakeFiles/cmTC_e9157.dir/src.c.o


# Object files for target cmTC_e9157
cmTC_e9157_OBJECTS = \
"CMakeFiles/cmTC_e9157.dir/src.c.o"

# External object files for target cmTC_e9157
cmTC_e9157_EXTERNAL_OBJECTS =

cmTC_e9157: CMakeFiles/cmTC_e9157.dir/src.c.o
cmTC_e9157: CMakeFiles/cmTC_e9157.dir/build.make
cmTC_e9157: /home/albrecht/software/petsc-intel-2018/linux-intel-64bit/lib/libpetsc.so
cmTC_e9157: CMakeFiles/cmTC_e9157.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/beckmann/pism/build/CMakeFiles/CMakeTmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cmTC_e9157"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmTC_e9157.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmTC_e9157.dir/build: cmTC_e9157

.PHONY : CMakeFiles/cmTC_e9157.dir/build

CMakeFiles/cmTC_e9157.dir/requires: CMakeFiles/cmTC_e9157.dir/src.c.o.requires

.PHONY : CMakeFiles/cmTC_e9157.dir/requires

CMakeFiles/cmTC_e9157.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cmTC_e9157.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cmTC_e9157.dir/clean

CMakeFiles/cmTC_e9157.dir/depend:
	cd /home/beckmann/pism/build/CMakeFiles/CMakeTmp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/beckmann/pism/build/CMakeFiles/CMakeTmp /home/beckmann/pism/build/CMakeFiles/CMakeTmp /home/beckmann/pism/build/CMakeFiles/CMakeTmp /home/beckmann/pism/build/CMakeFiles/CMakeTmp /home/beckmann/pism/build/CMakeFiles/CMakeTmp/CMakeFiles/cmTC_e9157.dir/DependInfo.cmake
.PHONY : CMakeFiles/cmTC_e9157.dir/depend

