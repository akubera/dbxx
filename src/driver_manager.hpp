/* 
 * File:   driver_manager.h
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 9:47 PM
 */

#pragma once


#include "cppdb.hpp"

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

CPPDB_NAMESPACE_BEGIN

// the default path to look for drivers
const fs::path driver_path_default("./build/drivers/");


class DriverManager
{
public:

    static void LoadDrivers(const std::string& path = driver_path_default.string());

    static std::vector<std::string> GetDriverNames(const std::string& path = driver_path_default.string());

protected:

};

CPPDB_NAMESPACE_END
