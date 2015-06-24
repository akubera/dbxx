/* 
 * File:   cppdb.cpp
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 7:45 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#include "../connection.hpp"

void usage();
int run_one_arg(const std::string&);

int drivers();
int version();

std::string cmd_name;

/*
 * 
 */
int main(int argc, char** argv)
{
  // build vector of strings
  vector<string> args(argv, argv + argc);

  cmd_name = args[0];

  if (args.size() == 1) {
    usage();
    return 0;
  }

  if (args.size() == 2) {
    return run_one_arg(args[1]);
  }

  return EXIT_FAILURE;
}

void
usage()
{
  cout << "Usage : " << cmd_name << " command <args>" << endl;
  cout << endl << ":commands " << endl;
  cout << "  drivers" "\t\t" "List all installed database drivers." << endl;
  cout << "  version" "\t\t" "Print the version of cppdb." << endl;
}

int
run_one_arg(const std::string& func_name)
{
  if (func_name == "drivers") {
    return drivers();
  }
  else if (func_name == "version") {
    return version();
  }

  return EXIT_FAILURE;
}

int
drivers()
{
  std::cout << "Found the following drivers:" << std::endl;
  for (auto driver : cppdb::DriverManager::GetDriverNames()) {
    std::cout << "\t" << driver << std::endl;
  }
  return EXIT_SUCCESS;
}

int
version()
{
  cout << "cppdb Version: " << "0.0.0" << std::endl;
  return EXIT_SUCCESS;
}
