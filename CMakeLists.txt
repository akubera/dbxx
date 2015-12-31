#
# CMakeLists.txt
# cppdb
# Andrew Kubera (andrewkubera@gmail.com)
#

cmake_minimum_required (VERSION 3.1.0)

project ( CppDB )


set (CPPDB_VERSION 0.0.1)

set (CMAKE_MACOSX_RPATH 1)
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/drivers)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_DOCS_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)

# Use environment variable CPPDB_PREFIX as the install prefix if set
if (NOT "$ENV{CPPDB_PREFIX}" STREQUAL "")
  set (CMAKE_INSTALL_PREFIX $ENV{CPPDB_PREFIX})
endif()

set(CMAKE_MACOSX_RPATH 1)

set (CMAKE_BUILD_TYPE Debug)

set (CMAKE_C_FLAGS "-O2 -Wall")
set (CMAKE_CXX_FLAGS "-O2 -Wall")

set (CMAKE_C_FLAGS_DEBUG   "-O0 -Wall -ggdb" )
set (CMAKE_CXX_FLAGS_DEBUG   "-O0 -Wall -ggdb" )

# use modern C++ library standard
include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)

if (COMPILER_SUPPORTS_CXX14)
  add_definitions("-std=c++14")
else()
  CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
if (COMPILER_SUPPORTS_CXX1Y)
  add_definitions("-std=c++1y" )
else()
  CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if (COMPILER_SUPPORTS_CXX11)
  add_definitions("-std=c++11")
else()
  CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if (COMPILER_SUPPORTS_CXX0X)
  add_definitions("-std=c++0x")
else()
  message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
endif()
endif()
endif()
endif()


option (MAKE_DOCS "Generate documentation (Requires SPHINX_EXE)" ON)

# Documentation setup
if (MAKE_DOCS)

  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen" VERBATIM)
  endif(DOXYGEN_FOUND)

endif(MAKE_DOCS)

# Require pkg-config
find_package (PkgConfig REQUIRED)

# Define driver options
option (DRIVER_MYSQL "Enable Support for mysql databases" OFF)
option (DRIVER_PGSQL93 "Enable Support for postgres-93 databases" OFF)
option (DRIVER_SQLITE "Enable Support for sqlite databases" OFF)
option (DRIVER_ODBC "Enable Support for connecting to databases using ODBC" OFF)

set (DRIVER_ERROR false)

if (DRIVER_MYSQL)
  find_package (MySQL)
  if (NOT ${MYSQL_FOUND})
    message (SEND_ERROR "Could not find 'MYSQL'")
    set (DRIVER_ERROR true)
  endif ()
endif (DRIVER_MYSQL)

if (DRIVER_PGSQL93)
  find_package (PGSQL)
  if (NOT ${PGSQL_FOUND})
    message (SEND_ERROR "Could not find 'PGSQL'")
    set (DRIVER_ERROR true)
  endif ()
endif (DRIVER_PGSQL93)

if (DRIVER_SQLITE)
  find_package (SQLITE)
  if (NOT ${SQLITE_FOUND})
    message (SEND_ERROR "Could not find 'SQLITE'")
    set (DRIVER_ERROR true)
  endif ()
endif (DRIVER_SQLITE)

if (DRIVER_ODBC)
  find_package (ODBC)
  if (NOT ${ODBC_FOUND})
    message (SEND_ERROR "Could not find 'ODBC'")
    set (DRIVER_ERROR true)
  endif ()
endif (DRIVER_ODBC)

if (DRIVER_ERROR)
  message (FATAL_ERROR "There were problems loading driver libraries")
endif (DRIVER_ERROR)

add_subdirectory (src)
add_subdirectory (test)
