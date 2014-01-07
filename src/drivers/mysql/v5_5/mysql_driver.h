/* 
 * File:   mysql_driver.h
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 9:42 PM
 */

#pragma once

#include "../../../driver.hpp"

class mysql_driver : public Driver
{
public:
    mysql_driver();
    mysql_driver(const mysql_driver& orig);
    virtual ~mysql_driver();

protected:

};
