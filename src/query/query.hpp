/*
 * File:   query.hpp
 * Author: andrewkubera
 *
 * Created on January 8, 2014, 5:35 PM
 */

#ifndef QUERY_HPP
#define	QUERY_HPP

#include "../cppdb.hpp"
#include "../types.hpp"

#include "query_result.hpp"

#include <cstdlib>
#include <string>
#include <tuple>
#include <memory>
#include <vector>

CPPDB_NAMESPACE_BEGIN

class Connection;

template <typename... _Tv>
class Query {
public:
  Query();
  Query(const Query& orig);
  virtual ~Query();

  Query<_Tv...>& select(const std::string&);
  Query<_Tv...>& where(const std::string&);
  Query<_Tv...>& from(const std::string&);

  cppdb::QueryResult<_Tv...> Exec(cppdb::Connection&);

  std::string toString();

protected:
  std::weak_ptr<Connection> _cnx_ptr;

  std::vector<std::string> _selects;

public:

  class Condition {
  public:

    Condition(const std::string&)
    {
    };
  };


};

CPPDB_NAMESPACE_END

// include the templates
#include "query.tcc"

typedef cppdb::Query<cppdb::SQLInt_t> IntQuery;

#endif //QUERY_HPP
