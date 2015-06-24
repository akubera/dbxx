#
# CMakeLists.txt
# cppdb
# Andrew Kubera (andrewkubera@gmail.com)
#

project ( CppDB )

cmake_minimum_required(VERSION 2.8.8)

set (CPPDB_VERSION 0.0.1)

set(CMAKE_MACOSX_RPATH 1)
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

## use c++11 libraries
set (CXX11_LIBS "")

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  string (STRIP "${GCC_VERSION}" GCC_VERSION)
  if (GCC_VERSION VERSION_LESS 4.9)
    message (WARNING "Using gcc with version ${GCC_VERSION}. gcc with version less than 4.9 does not satisfactorily comply with c++11 standards. Expect issues.")
  endif ()
  add_definitions ("-std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  add_definitions ("-std=c++11")
  # special linux+clang directives
  if ("${CMAKE_SYSTEM}" MATCHES "Linux")
     set (CXX11_LIBS "-lc++ -lc++abi -lm -lc -lgcc_s")
  endif()
endif ()

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
option (DRIVER_MYSQL "Enable Support for mysql databases" ON)
option (DRIVER_PGSQL93 "Enable Support for postgres databases" ON)
option (DRIVER_SQLITE "Enable Support for sqlite databases" OFF)
option (DRIVER_ODBC "Enable Support for connecting to databases using ODBC" ON)

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
