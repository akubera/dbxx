/*
 * File:   odbc_driver.hpp
 * Author: andrewkubera
 *
 * Created on January 16, 2014, 12:23 PM
 */

#pragma once

#include "../../driver.hpp"
#include "../../types.hpp"

#include "../../query/query.hpp"
#include "../../query/query_result.hpp"

// ODBC header
#include <sql.h>

// ODBC #define macros
#include <sqlext.h>

// ODBC typedefs
#include <sqltypes.h>

/**
 * \class odbc_driver
 * \brief CppDB Driver for ODBC connections
 */
class odbc_driver : public cppdb::Driver {
public:
  /**
   * Default Constructor
   */
  odbc_driver();

  /**
   * Copy Constructor
   */
  odbc_driver(const odbc_driver& orig);

  /**
   * Destructor
   */
  virtual ~odbc_driver();

  /**
   * Create a connection to a database from a set of parameters
   */
  cppdb::status_t Connect(const std::string& host,
                          const std::string& database,
                          cppdb::port_t port,
                          const std::string& username,
                          const std::string& password);


  /**
   * Disconnect from the database
   */
  cppdb::status_t Disconnect();

  void Query();

  /**
   * Execute a query
   *
   * @param query: Database query to be executed
   */
  template <typename... Tv>
  cppdb::QueryResult<Tv...> ExecQuery(const cppdb::Query<Tv...>& query);

  template <typename... Tv>
  cppdb::QueryResult<Tv...> Exec(cppdb::Connection&);

protected:
  /**
   * Internal method wrapping the ODBC method 'SQLBindCol'
   */
  template <typename T>
  void BindColumn(SQLHSTMT stmt,
                  SQLUSMALLINT col_num,
                  SQLPOINTER target_val_ptr,
                  SQLLEN buffsize,
                  SQLLEN * strlen);

protected:
  // sql environment
  SQLHENV _env;

  // sql connection
  SQLHDBC _hdbc;

  // sql status
  char _sql_stat[10];
};

// callable functions from outside the driver
extern "C" {
  cppdb::Driver* create_driver();
  void destroy_driver(cppdb::Driver* driver);
}

// include template implementations
#include "obdc_driver.tcc"
