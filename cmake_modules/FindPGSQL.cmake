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

  find_program (PG_CONFIG_EXE NAMES pg_config
                              PATHS /usr/bin/
                                    /usr/local/bin
                                    /usr/local/mysql/bin/
                                    /opt/bin/
                                    /opt/local/bin/)

  message (STATUS "PG_CONFIG_EXE '${PG_CONFIG_EXE}'")

  if (PG_CONFIG_EXE)
    exec_program (${PG_CONFIG_EXE} ARGS --cflags OUTPUT_VARIABLE PGSQL_FLAGS)
    exec_program (${PG_CONFIG_EXE} ARGS --includedir OUTPUT_VARIABLE PGSQL_INCLUDE_DIR)
    exec_program (${PG_CONFIG_EXE} ARGS --libdir OUTPUT_VARIABLE PGSQL_LIBDIR)
    exec_program (${PG_CONFIG_EXE} ARGS --libs OUTPUT_VARIABLE _PGSQL_LIBS)

    string (REGEX MATCHALL "-l[^ ]+" TMP_LIB_LIST "${_PGSQL_LIBS}")
    list (APPEND TMP_LIB_LIST "pq")

    message (STATUS "POSTGRES INCLUDE ${PGSQL_INCLUDE_DIR}")
    message (STATUS "PGSQL_LIBS ${TMP_LIB_LIST}")

    foreach (NEXT_LIB ${TMP_LIB_LIST})
      string (REPLACE "-l" "" _LIB ${NEXT_LIB})
      find_library ("FOUND_LIB_${T_LIB}" NAMES ${_LIB}
        PATHS ${PGSQL_LIBDIR}
        /usr/lib
        /usr/local/lib
        /usr/local/lib/pgsql
        /opt/local/lib
      )
      set (_NEXTLIB "${FOUND_LIB_${_LIB}}")
      list (APPEND PGSQL_LIBS "${FOUND_LIB_${_LIB}}")
    endforeach ()

    set (PGSQL_FOUND true)

  else ()
    message (STATUS "PG_CONFIG NOT FOUND!")
  endif ()


#  file(GLOB _PG_INCLUDES_FOUND /usr/local/include/postgresql-[0-9.]* /usr/include/postgresql-[0-9.]* /opt/include/postgresql-[0-9.]* /opt/local/include/postgresql-[0-9.]*)

#  foreach (NEXT_DIR ${_PG_INCLUDES_FOUND})
#    string (REGEX REPLACE "([0-9.]*)" "\\1" N_VERSION ${NEXT_DIR})
#    message(STATUS "NEXT_DIR :: '${NEXT_DIR}' - ${N_VERSION}")
#  endforeach ()

#  find_path (PostgreSQL_TYPE_INCLUDE_DIR NAMES catalog/pg_type.h PATHS /usr/local/ PATH_SUFFIXES pgsql/server include/server postgresql/server)

#  find_program (PGSQL_CONFIG NAMES pgsql_config
#                    PATHS /usr/local/pgsql/bin/
#                          /usr/local/bin
#                          /usr/bin/ )

#  set(PGSQL_FOUND true)
#  set(PGSQL_INCLUDE_DIR ${_PG_INCLUDES_FOUND})


endif (UNIX)

mark_as_advanced (
  PGSQL_INCLUDE_DIR
  PGSQL_LIBS
  PGSQL_FOUND
)

