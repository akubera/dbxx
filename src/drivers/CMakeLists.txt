#
# src/drivers/CMakeLists.txt
#

# An example library to use on all computers - has no requirements and does nothing
add_library(_dummy_driver SHARED dummy_driver.cpp)
target_link_libraries (_dummy_driver ${BOOST_LIBS})


# TODO : Add logic to only choose the drivers one selects to build


if (DRIVER_MYSQL)
add_subdirectory(mysql)
endif (DRIVER_MYSQL)

if (DRIVER_ODBC)
add_subdirectory(odbc)
endif (DRIVER_ODBC)


#add_subdirectory(postgres/v09_3)
