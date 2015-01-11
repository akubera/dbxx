/*
 * File:   odbc_driver.hpp
 * Author: andrewkubera
 *
 * Created on January 16, 2014, 12:23 PM
 */

#pragma once

#include "../../driver.hpp"
#include "../../types.hpp"

// ODBC header
#include <sql.h>

// ODBC #define macros
#include <sqlext.h>

// ODBC typedefs
#include <sqltypes.h>

/**
 * CppDB Driver for ODBC connections
 */
class odbc_driver : public cppdb::Driver {
public:
  odbc_driver();
  odbc_driver(const odbc_driver& orig);
  virtual ~odbc_driver();

  cppdb::status_t Connect(const std::string& host, const std::string& database, cppdb::port_t port, const std::string& username, const std::string& password);
  cppdb::status_t Disconnect();
  void Query();

protected:
  template <typename T>
  void BindColumn(SQLHSTMT stmt, SQLUSMALLINT col_num, SQLPOINTER  target_val_ptr, SQLLEN buffsize, SQLLEN * strlen);

protected:
  // sql environment
  SQLHENV _env;

  // sql connection
  SQLHDBC _hdbc;

  // sql status
  char  _sql_stat[10];
};

// callable functions from outside the driver
extern "C" {
  cppdb::Driver* create_driver();
  void destroy_driver(cppdb::Driver* driver);
}

// include template implementations
#include "obdc_driver.tcc"
