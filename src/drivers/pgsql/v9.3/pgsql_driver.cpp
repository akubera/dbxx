/*
 * File:   pgsql_driver.cpp
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 9:42 PM
 */

#include <cstdlib>
#include <iostream>

#include "pgsql_driver.h"

pgsql_driver::pgsql_driver():
  cppdb::Driver(),
  
  // Connect using library default parameters - we shouldn't do this here...
  _conn(PQconnectdb(nullptr))
{
  // this really should not happen...
  if (_conn == nullptr) {
    std::cerr << "ERROR : Insufficient memory to allocate a new PGconn object!\n";
    throw std::exception();
  }
}

pgsql_driver::pgsql_driver(const pgsql_driver& orig):
  cppdb::Driver(orig),
  _conn(PQconnectdb(nullptr)),
  _host(orig._host),
  _port(orig._port),
  _username(orig._username),
  _password(orig._password),
  _database(orig._database)
{
  if (orig._conn) {

  }
}

pgsql_driver::~pgsql_driver()
{
  if (_conn) {
    Disconnect();
  }
}

cppdb::status_t
pgsql_driver::Connect(const std::string& host, const std::string& database, cppdb::port_t port, const std::string& username, const std::string& password)
{
    //    mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag)
//    auto status = mysql_real_connect(_conn, host.c_str(), username.c_str(), password.c_str(), database.c_str(), port, nullptr, 0);
//    if (!status) {
//        std::cerr << "ERROR : " << mysql_error(_conn) << std::endl; //?
//        exit(EXIT_FAILURE);
//    }
  std::stringstream ss;
  ss << "dbname = " << database;
  _conn = PQconnectdb(ss.str().c_str());
  if (PQstatus(_conn) != CONNECTION_OK) {
    std::cerr << "Connection to database failed.\n";
    std::cerr << PQerrorMessage(_conn);
    PQfinish(_conn);
    _conn = nullptr;
    return 1;
  }
  return 0;
}

cppdb::status_t
pgsql_driver::Disconnect() {
  PQfinish(_conn);
  _conn = nullptr;    
  return 0;
}
