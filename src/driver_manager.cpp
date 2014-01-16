/*
 * File:   driver_manager.cpp
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 9:47 PM
 */

#include "driver_manager.hpp"

#include <regex>
#include <dlfcn.h>

CPPDB_NAMESPACE_BEGIN

std::map<std::string, void*> DriverManager::_drivers;

void
DriverManager::LoadDrivers(const std::string& path)
{
    fs::path driver_path(driver_path_default);

    if (!fs::is_directory(driver_path)) {
        std::cerr << "Error : Path " << fs::absolute(driver_path) << " is not a directory." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> res;

    fs::directory_iterator path_it(driver_path), end;
    for (; path_it != end; path_it++) {
        // if not a regular file, move on
        if (!fs::is_regular_file(path_it->path())) {
            continue;
        }

        // get filename from path iterator
        auto file_path = path_it->path();

        // store matches into a string match result
        std::smatch sm;

        // if it matches - add it to the result
        if (std::regex_match(file_path.filename().string(), sm, cppdb::driver_file_regex)) {
            void* handle = dlopen(fs::absolute(file_path).string().c_str(), RTLD_LAZY);
            if (handle == nullptr) {
                std::cerr << "Could not dlopen file '" << file_path.filename().string() << "'\n";
                std::cerr << " " << dlerror() << std::endl;
                exit(1);
            }
            _drivers[sm[1]] = handle;
        }

    }
}

std::vector<std::string>
DriverManager::GetDriverNames(const std::string& path)
{

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
        if (std::regex_match(filename, sm, cppdb::driver_file_regex)) {
            res.push_back(sm[1]);
        }

    }
    return res;
};

Driver*
DriverManager::GetDriverWithName(const std::string& driver_name) {
    auto found = _drivers.find(driver_name);
    if (found == _drivers.end()) {
        std::cerr << "[DriverManager::GetDriverWithName] WARNING Driver with name '" << driver_name << "' not found." << std::endl;
        return nullptr;
    }
    void *driver = found->second;
    auto create = (Driver* (*)())dlsym(driver, "create_driver");
    return create();
//    return nullptr;
}


CPPDB_NAMESPACE_END
