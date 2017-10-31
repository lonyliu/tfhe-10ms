# Install script for directory: /home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "release")
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
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/tfhe" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/lagrangehalfc_arithmetic.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/lwe-functions.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/lwebootstrappingkey.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/lwekey.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/lwekeyswitch.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/lweparams.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/lwesamples.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/numeric_functions.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/polynomials.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/polynomials_arithmetic.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/tfhe.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/tfhe_core.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/tfhe_garbage_collector.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/tfhe_gate_bootstrapping_functions.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/tfhe_gate_bootstrapping_structures.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/tfhe_generic_streams.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/tfhe_generic_templates.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/tfhe_io.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/tgsw.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/tgsw_functions.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/tlwe.h"
    "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/src/include/tlwe_functions.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/build/libtfhe/cmake_install.cmake")
  include("/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/build/test/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/ding/下载/zhounew/tfhe-tfhe-4247b21————temp/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
