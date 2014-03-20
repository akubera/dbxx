/*
 * odbc_test_0.cpp
 *
 */

#include "../src/connection.hpp"

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;
using namespace cppdb;

int main()
{
  cout << "ODBC Test : " << "00" << std::endl;

  Connection *cnx = new Connection("odbc://andrew:password@localhost/new_data");
  
  
  
  return 0;
}