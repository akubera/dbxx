#
# src/CMakeLists.txt
#

find_package(Boost 1.52.0 COMPONENTS filesystem system thread REQUIRED)
include_directories (${Boost_INCLUDE_DIR})

set (BOOST_LIBS ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY})

set (CPPDB_SRCS
  connection.cpp
  driver_manager.cpp
)

add_subdirectory (drivers)

add_library (cppdb ${CPPDB_SRCS})
target_link_libraries (cppdb ${BOOST_LIBS})

add_subdirectory (tools)
