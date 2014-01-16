/*
 * File:   odbc_driver.hpp
 * Author: andrewkubera
 *
 * Created on January 16, 2014, 12:23 PM
 */

#pragma once

#include "../../driver.hpp"

class odbc_driver : public cppdb::Driver {
public:
    odbc_driver();
    odbc_driver(const odbc_driver& orig);
    virtual ~odbc_driver();

protected:

};

