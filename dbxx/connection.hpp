///
/// \file connection.hpp
/// \author Andrew Kubera <andrew.kubera@gmail.com>
/// \date January 6, 2014, 5:07 PM EST
///

#pragma once

#include "cppdb.hpp"
#include "driver.hpp"
#include "driver_manager.hpp"
#include "exceptions.hpp"

#include <string>

CPPDB_NAMESPACE_BEGIN

/// \class Connection
/// \brief Connection class to a remote server.
///
/// Acts as a multiplexor, allowing multiple connections (presumably to multiple
/// databases) to a single server. The 'type' of database to connect to is
/// interpreted from the user.
///
template <typename Backend>
class Connection {
public:

  /// Create connection object without connecting to a server
  ///
  Connection();

  /// Create a connection based on a connection string
  ///
  /// \param cnx_string A string in the form of
  ///         "driver://[username:password@]host[:port][/database]"
  ///
  Connection(const std::string& cnx_string);

  /**
   * Create object and connect to a database
   *
   * @param db_name   Name of the database to select
   * @param host      Hostname or IP address of the server
   * @param username  Username of user
   * @param password  Password of the user
   * @param port      TCP port number the remote server is listening on
   */
  Connection(std::string const & db_name,
             std::string const & host,
             std::string const & username,
             std::string const & password,
             port_t const port);

  /**
   * Wrap a connection around an existing driver
   *
   * @param driver
   */
  Connection(Driver *driver);

  /**
   * Copy constructor
   *
   * Create a new connection using the same parameters as an existing
   * connection
   *
   * @param orig The original connection
   */
  Connection(const Connection& orig);

  /**
   * Destructor
   *
   * Destroy connection. Disconnects from server and destroys all tables.
   */
  virtual ~Connection();

protected:

  /**
   * A shared pointer to a concrete driver - created at the time of connection
   */
  std::shared_ptr<Driver> _driver;

};

CPPDB_NAMESPACE_END
