#
# src/CMakeLists.txt
#

set (CPPDB_SRCS
  connection.cpp
  driver_manager.cpp
)

add_subdirectory (drivers)

add_library (cppdb ${CPPDB_SRCS})

add_subdirectory (tools)
