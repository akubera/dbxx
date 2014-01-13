/* 
 * File:   driver_manager.cpp
 * Author: andrewkubera
 * 
 * Created on January 6, 2014, 9:47 PM
 */

#include "driver_manager.hpp"

#include <regex>

CPPDB_NAMESPACE_BEGIN

void
DriverManager::LoadDrivers(const std::string& path)
{

}

std::vector<std::string>
DriverManager::GetDriverNames(const std::string& path)
{
    // regex to match driver libraries (lib_<NAME>_driver.*)
    const std::regex driver_file_regex("lib_([^_]*)_driver\\..*");

    fs::path driver_path(driver_path_default);

    if (!fs::is_directory(driver_path)) {
        std::cerr << "Error : Path " << fs::absolute(driver_path) << " is not a directory." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> res;

    fs::directory_iterator path_it(driver_path), end;

    // loop through each subdirectory in 'driver_path'
    for (; path_it != end; path_it++) {
        // if not a regular file, move on
        if (!fs::is_regular_file(path_it->path())) {
            continue;
        }

        // get filename from path iterator
        auto filename = path_it->path().filename().string();

        // store matches into a string match result
        std::smatch sm;

        // if it matches - add it to the result
        if (std::regex_match(filename, sm, driver_file_regex)) {
            res.push_back(sm[1]);
        }

    }
    return res;
};

CPPDB_NAMESPACE_END
