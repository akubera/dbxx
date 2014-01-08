#
# src/CMakeLists.txt
#

find_package(Boost 1.52.0 COMPONENTS filesystem system REQUIRED)
include_directories (${Boost_INCLUDE_DIR})

set (CPPDB_SRCS
  connection.cpp
  driver_manager.cpp
)

add_subdirectory (drivers)

add_library (cppdb ${CPPDB_SRCS})
target_link_libraries (cppdb ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

add_subdirectory (tools)
