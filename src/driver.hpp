/* 
 * File:   driver.hpp
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 9:35 PM
 */

#pragma once

#include <vector>
#include <string>

class Driver {
public:
    Driver() {};
    Driver(const Driver& orig) {};
    virtual ~Driver() {};

    static void LoadDrivers(const std::string& path = "$DEFAULT_DRIVER_PATH$") {
        
    };

    static std::vector<std::string> GetDriverNames() {
        return std::vector<std::string>();
    };

protected:

};
