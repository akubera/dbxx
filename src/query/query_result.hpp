/*
 * File:   query_result.hpp
 * Author: andrewkubera
 *
 * Created on January 8, 2014, 5:51 PM
 */

#ifndef QUERY_RESULT_HPP
#define	QUERY_RESULT_HPP

#include "../cppdb.hpp"

#include <cstdlib>
#include <tuple>
#include <memory>

CPPDB_NAMESPACE_BEGIN

// Forward declare the other cppdb classes
class Connection;

template <typename... _Tv>
class Query;

template <typename... _Tv>
class Row;

template <typename... _Tv>
class QueryResult {
public:

  // Empty Query 
  QueryResult();
  QueryResult(const QueryResult& orig);

  virtual ~QueryResult();


  /**
   * Return a row at specified index
   *
   * @param rownumber The row to get 
   */
  Row<_Tv...> getRow(size_t rownumber);

  std::tuple<_Tv...> GetAsTuple(size_t index);

  Row<_Tv...> begin();
  Row<_Tv...> end();

protected:
  std::shared_ptr<Query<_Tv...>> _parent;
  std::weak_ptr<Connection> _cnx_ptr;
};

CPPDB_NAMESPACE_END

#include "query_result.tcc"

#endif	/* QUERY_RESULT_HPP */

