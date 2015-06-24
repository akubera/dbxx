/*
 * \file src/drivers/dummy_driver.cpp
 * \author Andrew Kubera
 * \date January 8, 2014, 6:16 PM
 */

#include "dummy_driver.hpp"

dummy_driver::dummy_driver():
  Driver("Dummy")
{
}

dummy_driver::dummy_driver(const dummy_driver& orig):
  Driver(orig._name)
{
}

dummy_driver::~dummy_driver()
{
}

cppdb::status_t
dummy_driver::Connect(const std::string& host, const std::string& database, cppdb::port_t port, const std::string& username, const std::string& password)
{
  return 0;
}

cppdb::status_t
dummy_driver::Disconnect()
{
  return 0;
}

cppdb::Driver*
create_driver()
{
  return new dummy_driver;
}

void
destroy_driver(cppdb::Driver* driver)
{
  delete driver;
}
