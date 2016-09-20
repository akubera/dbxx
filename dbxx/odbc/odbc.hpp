/**
 * \file dbxx/odbc/odbc.hpp
 * \date Sep 19, 2016
 * \brief Loader header of dbxx interface to odbc library.
 */


#pragma once

#include "../dbxx_macros.hpp"

#include <string>
#include <sstream>
#include <cstdio>

// load odbc files
#include <sql.h>
#include <sqlext.h>

DBXX_NAMESPACE_BEGIN

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
}

inline
std::string extract_error(
    const char *fn,
    SQLHANDLE handle,
    SQLSMALLINT type)
{
  SQLINTEGER i = 0;
  SQLINTEGER native;
  SQLCHAR state[ 7 ];
  SQLCHAR text [256];
  SQLSMALLINT len;

  std::stringstream ss;
  ss << "The driver reported the following diagnostics whilst running "
     << fn << "\n";

  SQLRETURN ret;
  do {
    ret = SQLGetDiagRec(type, handle, ++i, state, &native, text,
                        sizeof(text), &len );
    if (SQL_SUCCEEDED(ret)) {
      ss << state << ":"
         << i << ":"
         << native << ":"
         << text << "\n";
    }
  } while (ret == SQL_SUCCESS);

  return ss.str();
}

DBXX_NAMESPACE_END
