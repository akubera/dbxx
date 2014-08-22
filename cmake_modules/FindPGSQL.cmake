#
# cmake_modules/FindPGSQL.cmake
#
# Find the required components to use postgresql 
#
# Defines:
#  PGSQL_INCLUDE_DIR - the directory which contains mysql.h
#  PGSQL_LIBS - required libraries for mysql
#  PGSQL_FOUND - boolean stating whether this module was successful at finding mysql or not
#

message(STATUS "Finding Postgres")

set (PGSQL_FOUND false)

if (UNIX)

  file(GLOB _PG_INCLUDES_FOUND /usr/local/include/postgresql-[0-9.]* /usr/include/postgresql-[0-9.]* /opt/include/postgresql-[0-9.]* /opt/local/include/postgresql-[0-9.]*)

#  foreach (NEXT_DIR ${_PG_INCLUDES_FOUND})
#    string (REGEX REPLACE "([0-9.]*)" "\\1" N_VERSION ${NEXT_DIR})
#    message(STATUS "NEXT_DIR :: '${NEXT_DIR}' - ${N_VERSION}")
#  endforeach ()

#  find_path (PostgreSQL_TYPE_INCLUDE_DIR NAMES catalog/pg_type.h PATHS /usr/local/ PATH_SUFFIXES pgsql/server include/server postgresql/server)

#  find_program (PGSQL_CONFIG NAMES pgsql_config
#                    PATHS /usr/local/pgsql/bin/
#                          /usr/local/bin
#                          /usr/bin/ )

  set(PGSQL_FOUND true)
  set(PGSQL_INCLUDE_DIR ${_PG_INCLUDES_FOUND})
  set(PGSQL_LIBS /usr/lib/postgresql/libpgtypes.so /usr/lib/postgresql/libpq.so)


endif (UNIX)

mark_as_advanced (
  PGSQL_INCLUDE_DIR
  PGSQL_LIBS
  PGSQL_FOUND
)

