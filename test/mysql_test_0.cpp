/*
 * mysql_test_0.cpp
 *
 */

#include "../src/connection.hpp"
#include "../src/query/query.hpp"

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;
using namespace cppdb;

int main()
{
  cout << "MYSQL Test : " << "00" << std::endl;

  Connection *cnx = new Connection("mysql://andrew:password@localhost:3366/new_data");
  std::cout << "Connection " << (cnx == nullptr ? "unsuccessful" : "successful") << "\n";
  Query<string> q;



  
  return 0;
}
