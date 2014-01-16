#
# src/tools/CMakeLists.txt
#

set (CPPDB_CLI_SRCS
  cppdb.cpp
)

add_executable (cppdb_cli ${CPPDB_CLI_SRCS})
target_link_libraries (cppdb_cli cppdb)


