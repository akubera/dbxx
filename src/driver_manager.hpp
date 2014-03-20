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
#include <string>

CPPDB_NAMESPACE_BEGIN

// the default path to look for drivers
const std::string driver_path_default("./build/drivers/");

// regex to match driver libraries (lib_<NAME>_driver.*)
const std::regex driver_file_regex("lib_([^_]*)_driver\\..*");


class Driver;

/**
 * DriverManager
 *
 * Static class which handles loading of shared library files.
 */
class DriverManager
{
public:

    /**
     * LoadDrivers
     *
     * Parse through the driver path looking for any shared libraries which
     * match driver_file_regex, and load them (lazily) into the _driver_libraries map.
     * If drivers haven not been loaded, it will call LoadDrivers(). 
     */
    static void LoadDrivers(const std::string& path = driver_path_default);

    /**
     * UnloadDrivers
     *
     * Closes all connections and destroys all drivers.
     */
     static void UnloadDrivers();

    /**
     * UnloadDriver
     *
     * Kills all connections using driver with name 'name', then deletes the driver and 
     * unloads the shared library file.
     */
    static void UnloadDriver(const std::string& name);

    /**
     * GetDriverNames
     *
     * Returns a vector of driver names found in the driver path.
     */
    static std::vector<std::string> GetDriverNames(const std::string& path = driver_path_default);

    /**
     * GetDriverWithName
     *
     * Returns a shared pointer to the driver identified by string diver_name. If no driver
     * is found, it will return nullptr. If drivers haven not been loaded, it will call 
     * LoadDrivers().
     */
    static std::shared_ptr<Driver> GetDriverWithName(const std::string& driver_name);

    /** List of directories to search for */
    static std::vector<std::string> SearchPath;
    
protected:
    /** Map from names to drivers */
    static std::map<std::string, std::shared_ptr<Driver>> _drivers;
    
    /** Map from names to shared library objects */
    static std::map<std::string, void*> _driver_libraries;
    
    /** Bool set true when drivers are initialized */
    static bool _drivers_loaded;

protected:
    static std::shared_ptr<Driver> FindDriver(const std::string& driver_name);
    static std::shared_ptr<Driver> LoadDriver(void *, const std::string& name);
};

CPPDB_NAMESPACE_END
