///
/// \file dbxx/odbc/connection.hpp
///


#pragma once

#include "odbc.hpp"
#include <sql.h>
#include <sqlext.h>

#include <string>

DBXX_NAMESPACE_BEGIN


typedef std::basic_string<SQLCHAR> SqlString;


class Connection {
protected:
  /// SQL Environment
  HENV _env;

  /// Connection Handle
  HDBC _hdbc;

public:
  /// Create unconnected connection object
  Connection();

  /// Connect with a connection string
  Connection(const SqlString &cnx_str);
};

inline
Connection::Connection()
{
  auto status = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_env);
  if ((status != SQL_SUCCESS) && (status != SQL_SUCCESS_WITH_INFO)) {
    // std::string msg = "[odbc_driver::odbc_driver] ERROR : AllocHandle";
    throw std::exception();
  }
  status = SQLSetEnvAttr(_env, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, 0);
  if ((status != SQL_SUCCESS) && (status != SQL_SUCCESS_WITH_INFO)) {
    // std::string msg = "[odbc_driver::odbc_driver] ERROR : SQLSetEnvAttr";
    SQLFreeHandle(SQL_HANDLE_ENV, _env);
    throw std::exception();
  }

  status = SQLAllocHandle(SQL_HANDLE_DBC, _env, &_hdbc);

  if (!SQL_SUCCEEDED(status))
  {
    extract_error("SQLAllocHandle for dbc", _env, SQL_HANDLE_ENV);
    throw "Error";
  }

}

inline
Connection::Connection(const SqlString &cnx_str):
  Connection()
{
  auto cnx_cstr = const_cast<SQLCHAR*>(cnx_str.c_str());
  SQLConnect(_hdbc, cnx_cstr, SQL_NTS, 0, 0, 0, 0);
}




DBXX_NAMESPACE_END
