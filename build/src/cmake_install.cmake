# Install script for directory: /home/beckmann/pism/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/beckmann/pism")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpism.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpism.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpism.so"
         RPATH "/home/beckmann/pism/lib:/home/albrecht/software/petsc-intel-2018/linux-intel-64bit/lib:/p/system/packages/udunits/2.2.26/lib:/p/system/packages/fftw/3.3.7/lib:/p/system/packages/gsl/2.4/lib:/p/system/packages/netcdf-c/4.6.1/intel/parallel/lib:/p/system/packages/hdf5/1.10.2/intel/parallel/lib:/p/system/packages/szip/2.1/lib:/p/system/slurmdeps/17.11.2/build/zlib-1.2.11/lib:/p/system/packages/proj4/5.0.1/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY MESSAGE_LAZY FILES "/home/beckmann/pism/build/src/libpism.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpism.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpism.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpism.so"
         OLD_RPATH "/home/albrecht/software/petsc-intel-2018/linux-intel-64bit/lib:/p/system/packages/udunits/2.2.26/lib:/p/system/packages/fftw/3.3.7/lib:/p/system/packages/gsl/2.4/lib:/p/system/packages/netcdf-c/4.6.1/intel/parallel/lib:/p/system/packages/hdf5/1.10.2/intel/parallel/lib:/p/system/packages/szip/2.1/lib:/p/system/slurmdeps/17.11.2/build/zlib-1.2.11/lib:/p/system/packages/proj4/5.0.1/lib::::::::::::::::::::::::"
         NEW_RPATH "/home/beckmann/pism/lib:/home/albrecht/software/petsc-intel-2018/linux-intel-64bit/lib:/p/system/packages/udunits/2.2.26/lib:/p/system/packages/fftw/3.3.7/lib:/p/system/packages/gsl/2.4/lib:/p/system/packages/netcdf-c/4.6.1/intel/parallel/lib:/p/system/packages/hdf5/1.10.2/intel/parallel/lib:/p/system/packages/szip/2.1/lib:/p/system/slurmdeps/17.11.2/build/zlib-1.2.11/lib:/p/system/packages/proj4/5.0.1/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/p/system/packages/binutils/2.30/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpism.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismr" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismr")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismr"
         RPATH "/home/beckmann/pism/lib:/home/albrecht/software/petsc-intel-2018/linux-intel-64bit/lib:/p/system/packages/udunits/2.2.26/lib:/p/system/packages/fftw/3.3.7/lib:/p/system/packages/gsl/2.4/lib:/p/system/packages/netcdf-c/4.6.1/intel/parallel/lib:/p/system/packages/hdf5/1.10.2/intel/parallel/lib:/p/system/packages/szip/2.1/lib:/p/system/slurmdeps/17.11.2/build/zlib-1.2.11/lib:/p/system/packages/proj4/5.0.1/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE MESSAGE_LAZY FILES "/home/beckmann/pism/build/pismr")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismr" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismr")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismr"
         OLD_RPATH "/home/beckmann/pism/build/src:/home/albrecht/software/petsc-intel-2018/linux-intel-64bit/lib:/p/system/packages/udunits/2.2.26/lib:/p/system/packages/fftw/3.3.7/lib:/p/system/packages/gsl/2.4/lib:/p/system/packages/netcdf-c/4.6.1/intel/parallel/lib:/p/system/packages/hdf5/1.10.2/intel/parallel/lib:/p/system/packages/szip/2.1/lib:/p/system/slurmdeps/17.11.2/build/zlib-1.2.11/lib:/p/system/packages/proj4/5.0.1/lib:"
         NEW_RPATH "/home/beckmann/pism/lib:/home/albrecht/software/petsc-intel-2018/linux-intel-64bit/lib:/p/system/packages/udunits/2.2.26/lib:/p/system/packages/fftw/3.3.7/lib:/p/system/packages/gsl/2.4/lib:/p/system/packages/netcdf-c/4.6.1/intel/parallel/lib:/p/system/packages/hdf5/1.10.2/intel/parallel/lib:/p/system/packages/szip/2.1/lib:/p/system/slurmdeps/17.11.2/build/zlib-1.2.11/lib:/p/system/packages/proj4/5.0.1/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/p/system/packages/binutils/2.30/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismr")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pisms" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pisms")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pisms"
         RPATH "/home/beckmann/pism/lib:/home/albrecht/software/petsc-intel-2018/linux-intel-64bit/lib:/p/system/packages/udunits/2.2.26/lib:/p/system/packages/fftw/3.3.7/lib:/p/system/packages/gsl/2.4/lib:/p/system/packages/netcdf-c/4.6.1/intel/parallel/lib:/p/system/packages/hdf5/1.10.2/intel/parallel/lib:/p/system/packages/szip/2.1/lib:/p/system/slurmdeps/17.11.2/build/zlib-1.2.11/lib:/p/system/packages/proj4/5.0.1/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE MESSAGE_LAZY FILES "/home/beckmann/pism/build/pisms")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pisms" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pisms")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pisms"
         OLD_RPATH "/home/beckmann/pism/build/src:/home/albrecht/software/petsc-intel-2018/linux-intel-64bit/lib:/p/system/packages/udunits/2.2.26/lib:/p/system/packages/fftw/3.3.7/lib:/p/system/packages/gsl/2.4/lib:/p/system/packages/netcdf-c/4.6.1/intel/parallel/lib:/p/system/packages/hdf5/1.10.2/intel/parallel/lib:/p/system/packages/szip/2.1/lib:/p/system/slurmdeps/17.11.2/build/zlib-1.2.11/lib:/p/system/packages/proj4/5.0.1/lib:"
         NEW_RPATH "/home/beckmann/pism/lib:/home/albrecht/software/petsc-intel-2018/linux-intel-64bit/lib:/p/system/packages/udunits/2.2.26/lib:/p/system/packages/fftw/3.3.7/lib:/p/system/packages/gsl/2.4/lib:/p/system/packages/netcdf-c/4.6.1/intel/parallel/lib:/p/system/packages/hdf5/1.10.2/intel/parallel/lib:/p/system/packages/szip/2.1/lib:/p/system/slurmdeps/17.11.2/build/zlib-1.2.11/lib:/p/system/packages/proj4/5.0.1/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/p/system/packages/binutils/2.30/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pisms")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismv" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismv")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismv"
         RPATH "/home/beckmann/pism/lib:/home/albrecht/software/petsc-intel-2018/linux-intel-64bit/lib:/p/system/packages/udunits/2.2.26/lib:/p/system/packages/fftw/3.3.7/lib:/p/system/packages/gsl/2.4/lib:/p/system/packages/netcdf-c/4.6.1/intel/parallel/lib:/p/system/packages/hdf5/1.10.2/intel/parallel/lib:/p/system/packages/szip/2.1/lib:/p/system/slurmdeps/17.11.2/build/zlib-1.2.11/lib:/p/system/packages/proj4/5.0.1/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE MESSAGE_LAZY FILES "/home/beckmann/pism/build/pismv")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismv" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismv")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismv"
         OLD_RPATH "/home/beckmann/pism/build/src:/home/albrecht/software/petsc-intel-2018/linux-intel-64bit/lib:/p/system/packages/udunits/2.2.26/lib:/p/system/packages/fftw/3.3.7/lib:/p/system/packages/gsl/2.4/lib:/p/system/packages/netcdf-c/4.6.1/intel/parallel/lib:/p/system/packages/hdf5/1.10.2/intel/parallel/lib:/p/system/packages/szip/2.1/lib:/p/system/slurmdeps/17.11.2/build/zlib-1.2.11/lib:/p/system/packages/proj4/5.0.1/lib:"
         NEW_RPATH "/home/beckmann/pism/lib:/home/albrecht/software/petsc-intel-2018/linux-intel-64bit/lib:/p/system/packages/udunits/2.2.26/lib:/p/system/packages/fftw/3.3.7/lib:/p/system/packages/gsl/2.4/lib:/p/system/packages/netcdf-c/4.6.1/intel/parallel/lib:/p/system/packages/hdf5/1.10.2/intel/parallel/lib:/p/system/packages/szip/2.1/lib:/p/system/slurmdeps/17.11.2/build/zlib-1.2.11/lib:/p/system/packages/proj4/5.0.1/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/p/system/packages/binutils/2.30/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismv")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pism" TYPE FILE MESSAGE_LAZY FILES "/home/beckmann/pism/build/pism_config.nc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/pism" TYPE DIRECTORY MESSAGE_LAZY FILES "/home/beckmann/pism/src/" FILES_MATCHING REGEX "/[^/]*\\.hh$" REGEX "/[^/]*\\.h$" REGEX "/external$" EXCLUDE REGEX "/pythonbindings$" EXCLUDE REGEX "/doc$" EXCLUDE REGEX "/figs$" EXCLUDE REGEX "/ssa\\/tests$" EXCLUDE REGEX "/verification\\/tests\\/fortran$" EXCLUDE REGEX "/rheology\\/approximate$" EXCLUDE REGEX "/tracer$" EXCLUDE)
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/beckmann/pism/build/src/coupler/cmake_install.cmake")
  include("/home/beckmann/pism/build/src/earth/cmake_install.cmake")
  include("/home/beckmann/pism/build/src/external/cmake_install.cmake")
  include("/home/beckmann/pism/build/src/hydrology/cmake_install.cmake")
  include("/home/beckmann/pism/build/src/inverse/cmake_install.cmake")
  include("/home/beckmann/pism/build/src/regional/cmake_install.cmake")
  include("/home/beckmann/pism/build/src/rheology/cmake_install.cmake")
  include("/home/beckmann/pism/build/src/stressbalance/cmake_install.cmake")
  include("/home/beckmann/pism/build/src/util/cmake_install.cmake")
  include("/home/beckmann/pism/build/src/verification/cmake_install.cmake")

endif()

