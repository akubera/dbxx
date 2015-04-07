/*
 * test/query_test.cpp
 *
 */

#include "cppdb.hpp"
#include <iostream>

#include "orm_user.hpp"
#include "query/query.hpp"

int
main()
{
  cppdb::Query<int, std::string> q;
  q.select("id username").from("users").where("username = q");
  std::cout << q.toString() << "\n";
  return 0;
}


