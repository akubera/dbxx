/* 
 * File:   connection.cpp
 * Author: andrewkubera
 * 
 * Created on January 6, 2014, 5:07 PM
 */

#include "connection.hpp"

CPPDB_NAMESPACE_BEGIN

Connection::Connection()
{
}

Connection::Connection(const std::string& cnx_string)
{
}

Connection::Connection(const std::string& db_name, const std::string& host, const std::string& username, const std::string& password, port_t port)
{
}

Connection::Connection(const Connection& orig)
{
}

Connection::~Connection()
{
}

CPPDB_NAMESPACE_END
