#
# src/drivers/mysql/v5_5/CMakeLists.txt
#

set (MYSQL_DRIVER_SRCS
    mysql_driver.cpp)

include_directories (${MYSQL_INCLUDE_DIR})
add_library (_mysql_driver SHARED ${MYSQL_DRIVER_SRCS})
target_link_libraries (_mysql_driver ${MYSQL_LIBS} ${BOOST_LIBS})
