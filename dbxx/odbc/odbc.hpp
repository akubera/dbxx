/**
 * \file dbxx/odbc/odbc.hpp
 * \date Sep 19, 2016
 * \brief Loader header of dbxx interface to odbc library.
 */


#pragma once

#include "../dbxx_macros.h"

#include <string>
#include <cstdio>

// load odbc files
#include <sql.h>
#include <sqlext.h>

/**
 * Make connection to database using connection string
 *
 *
 */
void odbc_connect(const std::string &connection_string)
{
  static SQLHENV *env = nullptr;
  if (env == nullptr) {
    env = new SQLHENV;
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, env);
  }
    connection_string
}
