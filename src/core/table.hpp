/* 
 * File:   core/table.hpp
 * Author: Andrew Kubera <andrewkubera@gmail.com>
 *
 * Created on March 20, 2014, 7:58 PM
 */

#pragma once

#include "cppdb.hpp"

#include <string>


CPPDB_NAMESPACE_BEGIN

/**
 * Table
 *
 * Abstraction of database table functions.
 *
 */
class Table {
public:
  static Table* Create(const std::string& name)
  {
    return new Table();
  };

protected:
  Table(){};

};


CPPDB_NAMESPACE_END
