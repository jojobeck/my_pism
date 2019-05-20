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
CMAKE_SOURCE_DIR = /home/beckmann/pism

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/beckmann/pism/build

# Include any dependencies generated for this target.
include src/CMakeFiles/pismv.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/pismv.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/pismv.dir/flags.make

src/CMakeFiles/pismv.dir/pismv.cc.o: src/CMakeFiles/pismv.dir/flags.make
src/CMakeFiles/pismv.dir/pismv.cc.o: ../src/pismv.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beckmann/pism/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/pismv.dir/pismv.cc.o"
	cd /home/beckmann/pism/build/src && /p/system/packages/intel/parallel_studio_xe_2018_update1/compilers_and_libraries_2018.1.163/linux/mpi/intel64/bin/mpiicpc  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pismv.dir/pismv.cc.o -c /home/beckmann/pism/src/pismv.cc

src/CMakeFiles/pismv.dir/pismv.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pismv.dir/pismv.cc.i"
	cd /home/beckmann/pism/build/src && /p/system/packages/intel/parallel_studio_xe_2018_update1/compilers_and_libraries_2018.1.163/linux/mpi/intel64/bin/mpiicpc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beckmann/pism/src/pismv.cc > CMakeFiles/pismv.dir/pismv.cc.i

src/CMakeFiles/pismv.dir/pismv.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pismv.dir/pismv.cc.s"
	cd /home/beckmann/pism/build/src && /p/system/packages/intel/parallel_studio_xe_2018_update1/compilers_and_libraries_2018.1.163/linux/mpi/intel64/bin/mpiicpc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beckmann/pism/src/pismv.cc -o CMakeFiles/pismv.dir/pismv.cc.s

src/CMakeFiles/pismv.dir/pismv.cc.o.requires:

.PHONY : src/CMakeFiles/pismv.dir/pismv.cc.o.requires

src/CMakeFiles/pismv.dir/pismv.cc.o.provides: src/CMakeFiles/pismv.dir/pismv.cc.o.requires
	$(MAKE) -f src/CMakeFiles/pismv.dir/build.make src/CMakeFiles/pismv.dir/pismv.cc.o.provides.build
.PHONY : src/CMakeFiles/pismv.dir/pismv.cc.o.provides

src/CMakeFiles/pismv.dir/pismv.cc.o.provides.build: src/CMakeFiles/pismv.dir/pismv.cc.o


# Object files for target pismv
pismv_OBJECTS = \
"CMakeFiles/pismv.dir/pismv.cc.o"

# External object files for target pismv
pismv_EXTERNAL_OBJECTS =

pismv: src/CMakeFiles/pismv.dir/pismv.cc.o
pismv: src/CMakeFiles/pismv.dir/build.make
pismv: src/libpism.so
pismv: /home/albrecht/software/petsc-intel-2018/linux-intel-64bit/lib/libpetsc.so
pismv: /p/system/packages/udunits/2.2.26/lib/libudunits2.so
pismv: /p/system/packages/fftw/3.3.7/lib/libfftw3.so
pismv: /p/system/packages/gsl/2.4/lib/libgsl.so
pismv: /p/system/packages/gsl/2.4/lib/libgslcblas.so
pismv: /p/system/packages/netcdf-c/4.6.1/intel/parallel/lib/libnetcdf.so
pismv: /p/system/packages/hdf5/1.10.2/intel/parallel/lib/libhdf5.so
pismv: /p/system/packages/intel/parallel_studio_xe_2018_update1/compilers_and_libraries_2018.1.163/linux/compiler/lib/intel64/libimf.so
pismv: /p/system/packages/intel/parallel_studio_xe_2018_update1/compilers_and_libraries_2018.1.163/linux/compiler/lib/intel64/libiomp5.so
pismv: /p/system/packages/szip/2.1/lib/libsz.so
pismv: /p/system/slurmdeps/17.11.2/build/zlib-1.2.11/lib/libz.so
pismv: /usr/lib64/libdl.so
pismv: /usr/lib64/libm.so
pismv: /p/system/packages/hdf5/1.10.2/intel/parallel/lib/libhdf5_hl.so
pismv: /p/system/packages/proj4/5.0.1/lib/libproj.so
pismv: src/CMakeFiles/pismv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/beckmann/pism/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../pismv"
	cd /home/beckmann/pism/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pismv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/pismv.dir/build: pismv

.PHONY : src/CMakeFiles/pismv.dir/build

src/CMakeFiles/pismv.dir/requires: src/CMakeFiles/pismv.dir/pismv.cc.o.requires

.PHONY : src/CMakeFiles/pismv.dir/requires

src/CMakeFiles/pismv.dir/clean:
	cd /home/beckmann/pism/build/src && $(CMAKE_COMMAND) -P CMakeFiles/pismv.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/pismv.dir/clean

src/CMakeFiles/pismv.dir/depend:
	cd /home/beckmann/pism/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/beckmann/pism /home/beckmann/pism/src /home/beckmann/pism/build /home/beckmann/pism/build/src /home/beckmann/pism/build/src/CMakeFiles/pismv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/pismv.dir/depend

