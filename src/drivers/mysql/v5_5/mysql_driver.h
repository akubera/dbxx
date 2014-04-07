/*
 * File:   mysql_driver.h
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 9:42 PM
 */

#pragma once

#include <string>
#include <cstdlib>

#include <mysql.h>
#include "../../../driver.hpp"

class mysql_driver : public cppdb::Driver
{
public:
  // Default constructor
  mysql_driver();

  // Copy constructor
  mysql_driver(const mysql_driver& orig);

  // Destructor
  virtual ~mysql_driver();

  // Connect to database
  cppdb::status_t Connect(const std::string& host, const std::string& database, cppdb::port_t port, const std::string& username, const std::string& password);

  // Disconnect from the database and close the connection
  cppdb::status_t Disconnect();

  // Execute a query
  void ExecQueryString(const std::string& query)
  {
    // Send query 
    int err = mysql_real_query(_conn, query.c_str(), query.size());

    // if an error occurred
    if (err) {
      // TODO : handle error
      std::cerr << "Error " << mysql_errno(_conn) << " : " << mysql_error(_conn) << std::endl;
      return;
    }

    // Build the result -
    // The number of columns for the most recent query on the connection.
    MYSQL_RES * result = mysql_store_result(_conn);

    // no rows were returned
    if (result == nullptr) {
      if (mysql_field_count(_conn) != 0) {
          // error
      }
      else {
          // succes
      }
    }

    // data returned - parse through the result
    else {
      // store list of field name + field size pairs
      std::vector<std::pair<std::string, size_t>> returned_field_info;

      // number of fields returned by query
      size_t field_count = mysql_num_fields(result);

      // field info
      MYSQL_FIELD *field_array = mysql_fetch_fields(result);

      // loop through field info and build the field list
      for (size_t i = 0; i < field_count; i++) {
        returned_field_info.emplace_back(field_array[i].name, field_array[i].length);
      }

      // rows of vectors of strings
      std::vector<std::vector<std::string>> res;

      MYSQL_ROW row;

      // loop through each returned row of the query
      while ((row = mysql_fetch_row(result))) {
        // Convert the row to a vector of strings and add to the result  
//         res.push_back(std::vector<std::string>(row, row+field_count));        
        res.emplace_back(row, row+field_count);
      }

      // finally, delete the result
      mysql_free_result(result);
    }
  }

  void GetTables(const std::string& match = "")
  {
    const char *wild = (match == "" ? nullptr : match.c_str());
    MYSQL_RES *tables = mysql_list_tables(_conn, wild);
    if (tables == nullptr) {
        // error
    }
    // TODO : Build result
    mysql_free_result(tables);
  }

  void GetFields(const std::string& table, const std::string& match = "")
  {
    const char *wild = (match == "" ? nullptr : match.c_str());
    MYSQL_RES *fields = mysql_list_fields(_conn, table.c_str(), wild);
    if (fields == nullptr) {
        // error
    }

    size_t field_cnt = mysql_num_fields(fields);
    for (size_t i = 0; i < field_cnt; ++i) {
      MYSQL_FIELD *col = mysql_fetch_field_direct(fields, i);
      std::cout << "Column " << i << ": " << col->name << std::endl;
    }
    mysql_free_result(fields);
  }

  /** MYSQL Default port */
  cppdb::port_t DefaultPort()
  {
    return 3306;
  }

protected:
  // The connection
  MYSQL *_conn;

  std::string _host;
  cppdb::port_t _port;

  std::string _username;
  std::string _password;
  std::string _database {""};

  MYSQL_RES *res;
  MYSQL_ROW row;
};
