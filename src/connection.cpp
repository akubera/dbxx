///
/// \file connection.cpp
/// \author Andrew Kubera <andrew.kubera@gmail.com>
/// \date January 6, 2014, 5:07 PM EST
///

#include "connection.hpp"
#include "driver_manager.hpp"

#include <iostream>
#include <cassert>

CPPDB_NAMESPACE_BEGIN

Connection::Connection()
{
}

Connection::Connection(const std::string& cnx_string)
{
  std::cout << "[Connection::Connection]\n";
  const std::string protocol_delimeter{"://"};

  std::string hostname, port_string, db_name, username, password;

  // pointer finds the "://" marking the end of the driver name
  auto ptr = cnx_string.find(protocol_delimeter);

  if (ptr == std::string::npos) {
    std::cerr << "ERROR : No protocol specified by 'protocol://...' in"
                 " connection string : '" << cnx_string << "'" << std::endl;
    throw std::exception();
  }

  std::string protocol(cnx_string.begin(), cnx_string.begin() + ptr);

  // point to past the delimeter
  ptr += protocol_delimeter.size();

  // now we either read a hostname or username+password combination scan for
  // an '@' sign
  auto at_position = cnx_string.find("@", ptr);

  // found an '@' char, read in the username + password
  if (at_position != std::string::npos) {

    // find the first colon BEFORE the '@'
    auto colon_position = cnx_string.rfind(":", at_position);

    // if the colon is before our current position, throw an error because
    // we have just found the one in "://"
    if (colon_position <= ptr) {
      std::cerr << "ERROR : Malformed connection string - "
              "Expected colon separator ':' before '@' when specifying "
              "username and password." << std::endl;
      throw std::exception();
    }

    // ensure there is exactly one colon between :// and '@'
    if (std::count(cnx_string.begin() + ptr, cnx_string.begin() + at_position, ':') != 1) {
      std::cerr << "ERROR : Malformed connection string - "
              "Expected exactly one (1) colon separator ':' before '@' when "
              "specifying username and password in string "
              "'" << cnx_string << "'"
              << std::endl;
      throw std::exception();
    }

    username = std::string(cnx_string.begin() + ptr, cnx_string.begin() + colon_position);
    password = std::string(cnx_string.begin() + colon_position + 1, cnx_string.begin() + at_position);

    ptr = at_position + 1;
  }
  // no '@' char, use the default username and password?
  else {

  }

  // ptr now points to beginning of hostname - find either next ':' or '/'
  std::size_t next_delim_position = cnx_string.find_first_of(":/", ptr);

  // no colon nor slash - copy hostname to the end
  if (next_delim_position == std::string::npos) {
    hostname = cnx_string.substr(ptr);
  }
  else {
    hostname = cnx_string.substr(ptr, next_delim_position - ptr);
  }

  if (next_delim_position == std::string::npos) {

  }

  // colon means port is specified
  else if (cnx_string[next_delim_position] == ':') {
    std::cout << "COLON " << next_delim_position << ' ' << ptr << std::endl;

    // find a slash
    std::size_t slash_pos = cnx_string.find('/', next_delim_position);

    // if slash exists after colon, copy up to the colon into portname,
    // everything after into db_name
    if (slash_pos != std::string::npos) {
      port_string = cnx_string.substr(next_delim_position + 1,
                                      slash_pos - (next_delim_position + 1));
      db_name = cnx_string.substr(slash_pos + 1);
    }

    // no slash, copy to end of string
    else {
      port_string = cnx_string.substr(next_delim_position + 1);
    }
  }

  // a slash punctuated the hostname
  else {
    db_name = cnx_string.substr(next_delim_position + 1);
  }

  std::cout << "Read in driver '" << protocol << "'\n";
  std::cout << "Read in username '" << username << "' and password '"
            << password << "'" << std::endl;
  std::cout << "Read in hostname '" << hostname << "'\n";
  std::cout << "Read in port '" << port_string << "'\n";
  std::cout << "Read in database name '" << db_name << "'" << std::endl;

  cppdb::port_t port_num = std::stoi(port_string);

  // load the drivers
  _driver = DriverManager::GetDriverWithName(protocol);
  std::cout << "Loaded driver " << _driver << "\n";

  if (_driver == nullptr) {
    throw new NoDriverException;
  }

  status_t status = _driver->Connect(hostname, db_name, port_num, username,
                                      password);
  std::cout << "Connection returned " << status << "\n";
}

Connection::Connection(const std::string& db_name,
                       const std::string& host,
                       const std::string& username,
                       const std::string& password,
                       port_t port)
{
}

Connection::Connection(Driver *driver)
{

}

Connection::Connection(const Connection& orig)
{
}

Connection::~Connection()
{
}

CPPDB_NAMESPACE_END
