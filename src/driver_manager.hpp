/* 
 * File:   driver_manager.h
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 9:47 PM
 */

#pragma once


#include "cppdb.hpp"
#include "driver.hpp"

#include <map>
#include <regex>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

CPPDB_NAMESPACE_BEGIN

// the default path to look for drivers
const fs::path driver_path_default("./build/drivers/");

// regex to match driver libraries (lib_<NAME>_driver.*)
const std::regex driver_file_regex("lib_([^_]*)_driver\\..*");


class DriverManager
{
public:

    static void LoadDrivers(const std::string& path = driver_path_default.string());

    static std::vector<std::string> GetDriverNames(const std::string& path = driver_path_default.string());

    static Driver* GetDriverWithName(const std::string& driver_name);

protected:
    static std::map<std::string, void*> _drivers;
};

CPPDB_NAMESPACE_END
