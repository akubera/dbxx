#
# cmake_modules/FindODBC.cmake
#
# Find the ODBC compilation information
#
# Defines:
#  ODBC_INCLUDE_DIR - the directory which contains sql.h
#  ODBC_LIBS - required libraries for mysql
#  ODBC_FOUND - boolean stating whether this module was successful at finding mysql or not
#

if (UNIX)

    find_program (ODBC_CONFIG_EXE NAMES odbc_config
                    PATHS /usr/bin/
                          /usr/local/bin
                          /opt/bin/
                          /opt/local/bin )

    if (ODBC_CONFIG_EXE)
        message (STATUS "Using odbc_config: ${ODBC_CONFIG_EXE}")

        # extract the -I information from `mysql_config --include` and store into TMP_INCLUDE_DIR
        exec_program (${ODBC_CONFIG_EXE} ARGS --include-prefix OUTPUT_VARIABLE TMP_INCLUDE_DIR)

        # extract the library location from `odbc_config --lib-prefix`
        exec_program(${ODBC_CONFIG_EXE} ARGS --lib-prefix OUTPUT_VARIABLE TMP_ODBC_LIB_DIR)

    else (ODBC_CONFIG_EXE)
        message (WARNING "No odbc_config found: is it installed? Now randomly guessing locations of unixODBC.")
    endif (ODBC_CONFIG_EXE)

    # find the sql.h file in the paths
    find_path (ODBC_INCLUDE_DIR NAMES sql.h
        HINTS ${TMP_INCLUDE_DIR}
              /usr/include
              /usr/local/include
              /opt/local/include )

    if (NOT ODBC_INCLUDE_DIR)
        status (WARNING "Could not find header file 'sql.h'")
    endif (NOT ODBC_INCLUDE_DIR)

    find_library(ODBC_LIBS NAMES odbc
        PATHS ${TMP_ODBC_LIB_DIR}
              /usr/lib
              /usr/local/lib
              /opt/lib
              /opt/local/lib)

    if (NOT ODBC_LIBS)
        status (WARNING "Could not find library 'libodbc'")
    endif (NOT ODBC_LIBS)

    set (ODBC_FOUND (ODBC_LIBS AND ODBC_INCLUDE_DIR))

else (UNIX)
    # TODO : Handle Windows searching
endif (UNIX)

mark_as_advanced (ODBC_INCLUDE_DIR ODBC_LIBS ODBC_FOUND)
