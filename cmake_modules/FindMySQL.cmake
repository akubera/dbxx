#
# cmake_modules/FindMySQL.cmake
#
# Find the MySQL includes
#
# Defines:
#  MYSQL_INCLUDE_DIR - the directory which contains mysql.h
#  MYSQL_LIBS - required libraries for mysql
#  MYSQL_FOUND - boolean stating whether this module was successful at finding mysql or not
#

set (MYSQL_LIBS "")

if (UNIX)

    find_program (MYSQL_CONFIG NAMES mysql_config mysql_config5
                    PATHS /usr/local/mysql/bin/
                          /usr/local/bin
                          /usr/bin/ )

    if (MYSQL_CONFIG)
        message (STATUS "Using mysql-config: ${MYSQL_CONFIG}")

        # extract the -I information from `mysql_config --include` and store into TMP_INCLUDE_DIR
        exec_program (${MYSQL_CONFIG} ARGS --include OUTPUT_VARIABLE TMP_INCLUDE)
        string (REGEX REPLACE "-I([^ ]*)( .*)?" "\\1" TMP_INCLUDE_DIR "${TMP_INCLUDE}")

        # find the mysql.h file in the paths
        find_path (MYSQL_INCLUDE_DIR mysql.h
            ${TMP_INCLUDE_DIR}
            /usr/local/include
            /usr/local/include/mysql
            /opt/local/include
            /opt/local/include/mysql)

        # extract the libraries and paths from `mysql_config --libs`
        exec_program(${MYSQL_CONFIG} ARGS --libs OUTPUT_VARIABLE TMP_LIBS)
        string(REGEX MATCHALL "-l[^ ]+" TMP_LIB_LIST "${TMP_LIBS}")
        string(REGEX MATCHALL "-L[^ ]+" TMP_LIB_PATHS "${TMP_LIBS}")

        # loop through paths - removing -L and storing into LIB_PATHS
        foreach (LIB_P ${TMP_LIB_PATHS})
            # remove -L prefix
            string (REPLACE "-L" "" T_PATH "${LIB_P}")
            list (APPEND LIB_PATHS "${T_PATH}")
        endforeach ()

        # loop through libs : finding the libraries and storing them in the right places
        foreach (NEXT_LIB ${TMP_LIB_LIST})
            string (REPLACE "-l" "" T_LIB ${NEXT_LIB})
            find_library ("FOUND_LIB_${T_LIB}" NAMES ${T_LIB}
                PATHS ${LIB_PATHS} 
                /usr/local/lib
                /usr/local/lib/mysql
            )
            list (APPEND MYSQL_LIBS "${FOUND_LIB_${T_LIB}}")
        endforeach ()

        # we have found MySQL
        set (MYSQL_FOUND true)

    else (MYSQL_CONFIG)
        message (STATUS "No mysql-config found: is it installed? Now randomly guessing.")
        set (MYSQL_ADD_LIBRARIES "")
        list (APPEND MYSQL_LIBRARIES "mysqlclient m")
        set (MYSQL_FOUND false)
    endif (MYSQL_CONFIG)

else (UNIX)
    # TODO : Handle Windows searching
endif (UNIX)

mark_as_advanced (MYSQL_INCLUDE_DIR MYSQL_LIBS MYSQL_FOUND)
