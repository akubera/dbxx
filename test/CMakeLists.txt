#
# test/CMakeLists.txt
#

include_directories (../src)

set (TEST_SRCS
  main.cpp
)

add_executable (test ${TEST_SRCS})

add_executable (odbc_test_0 odbc_test_0.cpp)
target_link_libraries(odbc_test_0 cppdb)
