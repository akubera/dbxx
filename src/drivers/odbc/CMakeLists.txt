#
# src/drivers/odbc/CMakeLists.txt
#

find_package (ODBC REQUIRED)

set (ODBC_DRIVER_SRCS
    odbc_driver.cpp)

include_directories (${ODBC_INCLUDE_DIR})
add_library (_odbc_driver SHARED ${ODBC_DRIVER_SRCS})
target_link_libraries (_odbc_driver ${ODBC_LIBS} ${BOOST_LIBS})
