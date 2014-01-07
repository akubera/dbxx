/* 
 * File:   mysql_driver.h
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 9:42 PM
 */

#pragma once

#include <string>

#include <mysql.h>
#include "../../../driver.hpp"

class mysql_driver : public Driver
{
public:
    mysql_driver();
    mysql_driver(const mysql_driver& orig);
    virtual ~mysql_driver();
    
    int Connect(const std::string& host, const std::string& database, cppdb::port_t port, const std::string& username, const std::string& password);

protected:
    MYSQL *_conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
};
