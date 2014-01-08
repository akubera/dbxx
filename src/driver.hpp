/* 
 * File:   driver.hpp
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 9:35 PM
 */

#pragma once

#include <vector>
#include <string>
#include "cppdb.hpp"

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

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

    virtual int Connect(const std::string& host, const std::string& database, cppdb::port_t port, const std::string& username, const std::string& password) = 0;

    static void LoadDrivers(const std::string& path = "$DEFAULT_DRIVER_PATH$")
    {

    };

    static std::vector<std::string> GetDriverNames()
    {
        fs::path p("..");
        std::cout << fs::absolute(p) << std::endl;
        std::vector<std::string> res;
        res.push_back("one");
        return res;
    };

protected:

};
