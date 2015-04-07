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

add_executable (mysql_test_0 mysql_test_0.cpp)
target_link_libraries(mysql_test_0 cppdb)

add_executable (query_test_0 query_test.cpp)
target_link_libraries(query_test_0 cppdb)

