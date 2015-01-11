#
# src/drivers/pgsql/v9.3/CMakeLists.txt
#

set (POSTGRES_DRIVER_SRCS
    pgsql_driver.cpp)

include_directories (${PGSQL_INCLUDE_DIR})
add_library (_pgsql93_driver SHARED ${POSTGRES_DRIVER_SRCS})
target_link_libraries (_pgsql93_driver ${PGSQL_LIBS} ${BOOST_LIBS})
