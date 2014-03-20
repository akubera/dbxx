/*
 * File:   mysql_driver.cpp
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 9:42 PM
 */

#include <cstdlib>
#include <iostream>

#include "mysql_driver.h"

mysql_driver::mysql_driver() :
    _conn(mysql_init(nullptr))
{
    // this really should not happen...
    if (_conn == nullptr) {
        std::cerr << "ERROR : Insufficient memory to allocate a new MYSQL object." << std::endl;
        throw std::exception();
    }
}

mysql_driver::mysql_driver(const mysql_driver& orig) :
  _conn(mysql_init(nullptr)),
  _host(orig._host),
  _port(orig._port),
  _username(orig._username),
  _password(orig._password),
  _database(orig._database)
{
    auto status = mysql_real_connect(_conn, _host.c_str(), _username.c_str(), _password.c_str(), _database.c_str(), _port, nullptr, 0);
    if (!status) {
        std::cerr << "ERROR : " << mysql_error(_conn) << std::endl;
        exit(EXIT_FAILURE);
    }

    if (orig._conn) {

    }
}

mysql_driver::~mysql_driver()
{
    if (_conn) {
        mysql_close(_conn);
    }
    _conn = nullptr;
}

cppdb::status_t
mysql_driver::Connect(const std::string& host, const std::string& database, cppdb::port_t port, const std::string& username, const std::string& password)
{
    //    mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag)
    auto status = mysql_real_connect(_conn, host.c_str(), username.c_str(), password.c_str(), database.c_str(), port, nullptr, 0);
    if (!status) {
        std::cerr << "ERROR : " << mysql_error(_conn) << std::endl; //?
        exit(EXIT_FAILURE);
    }
    return 0;
}

cppdb::status_t
mysql_driver::Disconnect() {
    mysql_close(_conn);
    _conn = nullptr;
    return 0;
}

cppdb::Driver*
create_driver()
{
    return new mysql_driver;
}

void
destroy_driver(cppdb::Driver* driver)
{
    delete driver;
}

