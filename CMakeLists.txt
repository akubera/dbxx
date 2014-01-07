#
# CMakeLists.txt
# cppdb
# Andrew Kubera (andrewkubera@gmail.com)
#

project ( CppDB )

cmake_minimum_required(VERSION 2.8.8)

set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

set (CMAKE_BUILD_TYPE Debug)

set (CMAKE_C_FLAGS "-O2 -Wall")
set (CMAKE_CXX_FLAGS "-O2 -Wall")

set (CMAKE_C_FLAGS_DEBUG   "-O0 -Wall -ggdb" )
set (CMAKE_CXX_FLAGS_DEBUG   "-O0 -Wall -ggdb" )

## use c++11 libraries

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
  add_definitions ("-std=c++11")
else ()
  if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    add_definitions ("-std=c++11 -stdlib=libstdc++")
  endif()
endif ()


# Require pkg-config
find_package (PkgConfig REQUIRED)

add_subdirectory (src)
add_subdirectory (test)
