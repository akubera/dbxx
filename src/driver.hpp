/*
 * File:   driver.hpp
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 9:35 PM
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <regex>

#include "types.hpp"
#include "cppdb.hpp"

CPPDB_NAMESPACE_BEGIN

class Driver {
public:

  Driver()
  {
  };

  Driver(const Driver& orig)
  {
  };

  virtual ~Driver()
  {
  };

  /**
   * Connect to a server
   *
   * @param host Hostname of the server to connect to
   * @param database Name of the database to use
   * @param port Port number of the remote server
   * @param username A username to authenticate with server
   * @param password A password to authenticate the username
   *
   * @return Execution status
   */
  virtual status_t Connect(const std::string& host, const std::string& database, cppdb::port_t port, const std::string& username, const std::string& password) = 0;

  /**
   * Disconnect from the server.
   * If Connected
   *
   * @return Execution status
   */
  virtual status_t Disconnect() = 0;

  /**
   * Get the name of the driver
   * @return
   */
  std::string Name()
  {
    return _name;
  }

protected:

  Driver(const std::string& name) :
  _name(name)
  {
    std::cout << "Constructing Driver '" << _name << "'" << std::endl;
  };

  const std::string _name;

};

CPPDB_NAMESPACE_END
