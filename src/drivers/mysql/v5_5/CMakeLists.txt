#
# src/drivers/mysql/v5_5/CMakeLists.txt
#

set (MYSQL_DRIVER_SRCS
    mysql_driver.cpp)

include_directories (${MYSQL_INCLUDE_DIR})
add_library (mysql_5_5 SHARED ${MYSQL_DRIVER_SRCS})
target_link_libraries (mysql_5_5 ${MYSQL_LIBS})
