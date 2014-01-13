/* 
 * File:   driver.hpp
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 9:35 PM
 */

#pragma once

#include <vector>
#include <string>
#include <regex>

#include "cppdb.hpp"

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

// the default path to look for drivers
const fs::path driver_path_default("./build/drivers/");

CPPDB_NAMESPACE_BEGIN

class Driver
{
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
     * @param port Port number of the 
     * @param username A username to authenticate with server
     * @param password A password to authenticate the username
     * 
     * @return Status
     */
    virtual int Connect(const std::string& host, const std::string& database, cppdb::port_t port, const std::string& username, const std::string& password) = 0;


protected:

};

CPPDB_NAMESPACE_END
