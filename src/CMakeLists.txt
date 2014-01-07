#
# src/CMakeLists.txt
#

set (CPPDB_SRCS
  connection.cpp
)

add_subdirectory (drivers)

add_library (cppdb ${CPPDB_SRCS})

add_subdirectory (tools)
