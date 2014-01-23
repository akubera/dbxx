/* 
 * File:   driver_manager.cpp
 * Author: andrewkubera
 * 
 * Created on January 6, 2014, 9:47 PM
 */

#include "driver_manager.hpp"

#include <regex>
#include <dlfcn.h>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;


CPPDB_NAMESPACE_BEGIN

std::map<std::string, void*> DriverManager::_driver_libraries;
std::map<std::string, std::shared_ptr<Driver>> DriverManager::_drivers;
bool DriverManager::_drivers_loaded = false;
std::vector<std::string> DriverManager::SearchPath {driver_path_default};

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
            _driver_libraries[sm[1]] = handle;
        }

    }
    DriverManager::_drivers_loaded = true;
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
}

std::shared_ptr<Driver>
DriverManager::FindDriver(const std::string& driver_name) {
  
  const std::regex file_regex("lib_"+driver_name+"_driver\\..*");
  for (const auto& dir : SearchPath) {
    
  }    
  // not implemented...
  assert(false);
}

std::shared_ptr<Driver>
DriverManager::GetDriverWithName(const std::string& driver_name) {
    if (!_drivers_loaded) {
        LoadDrivers();
    }
    auto found = _drivers.find(driver_name);
    if (found != _drivers.end()) {
        return found->second;
    }

    auto found_lib = _driver_libraries.find(driver_name);
    if (found_lib != _driver_libraries.end()) {
        return LoadDriver(found_lib->second, driver_name);
    }

    std::cerr << "[DriverManager::GetDriverWithName] WARNING Driver with name '" << driver_name << "' not found." << std::endl;
    return nullptr;
}

std::shared_ptr<Driver>
DriverManager::LoadDriver(void *lib, const std::string& name) {
    auto create = (Driver* (*)())dlsym(lib, "create_driver");
    std::shared_ptr<Driver> res(create());
    _drivers[name] = res;
    return res;
}

void
DriverManager::UnloadDriver(const std::string& name)
{
    // find the library
    auto lib_finder = _driver_libraries.find(name);
    // find the driver object
    auto found = _drivers.find(name);
    
    // the driver with name 'name' was not loaded - do nothing
    if (lib_finder == _driver_libraries.end()) {
        return;
    }
    
    // load the destroy function
    auto destroy = (void (*)(Driver*))dlsym(lib_finder->second, "destroy_driver");
    
    // destroy the object
    if (found->second.unique()) {
        auto driver = found->second.get();
        found->second.reset();
        destroy(driver);        
    }

    // close the shared library
    int status = dlclose(lib_finder->second);
    if (status == -1) {
        dlerror();
    }
}
    

CPPDB_NAMESPACE_END
