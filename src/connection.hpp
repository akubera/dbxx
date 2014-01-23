/* 
 * File:   connection.hpp
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 5:07 PM
 */

#pragma once

#include "cppdb.hpp"
#include "driver.hpp"
#include "driver_manager.hpp"

#include <string>

CPPDB_NAMESPACE_BEGIN

class Connection
{
public:

    /**
     * Create connection object without connecting to a server
     */
    Connection();

    /**
     * Create a connection based on a connection string
     *
     * @param cnx_string A string in the form of "driver://[username:password@]host[:port][/database]"
     */
    Connection(const std::string& cnx_string);

    /**
     * Create object and connect to a database
     *
     * @param db_name   Name of the database to select
     * @param host      Hostname or IP address of the 
     * @param username  Username of user with 
     * @param password  Password of the user with permission to 
     * @param port      TCP port number the remote server is listening to
     */
    Connection(const std::string& db_name, const std::string& host, const std::string& username, const std::string& password, port_t port);

    /**
     * Create a new connection using the same parameters as an existing connection
     *
     * @param orig The original connection
     */
    Connection(const Connection& orig);

    /**
     * Destroy connection. Disconnects from server and destroys all tables.
     */
    virtual ~Connection();



protected:

  std::shared_ptr<Driver> _driver;

};

CPPDB_NAMESPACE_END
