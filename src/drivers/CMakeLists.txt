#
# src/drivers/CMakeLists.txt
#

# An example library to use on all computers - has no requirements and does nothing
add_library(_dummy_driver SHARED dummy_driver.cpp)
target_link_libraries (_dummy_driver ${BOOST_LIBS})


# TODO : Add logic to only choose the drivers one selects to build

find_package (MySQL)

if (${MYSQL_FOUND})
add_subdirectory(mysql)
endif (${MYSQL_FOUND})

find_package (ODBC)

if (${ODBC_FOUND})
add_subdirectory(odbc)
endif (${ODBC_FOUND})

#add_subdirectory(postgres/v09_3)
