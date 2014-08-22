/* 
 * File:   row.hpp
 * Author: andrewkubera
 *
 * Created on January 8, 2014, 5:48 PM
 */

#ifndef ROW_HPP
#define	ROW_HPP

#include "../cppdb.hpp"
#include "../types.hpp"

CPPDB_NAMESPACE_BEGIN

/**
 * Row is a single result element from an executed query
 */
template <typename... _Tv>
class Row {
public:
  Row();
  Row(QueryResult<_Tv...>*);
  Row(const Row& orig);
  virtual ~Row();

  static Row<_Tv...> EmptyRow();

protected:
  /**
   * Position index of row in query result
   */
  size_t _index;

  /**
   * An empty row which is used to denote the end of a query result
   */
  bool _empty{false};

  QueryResult<_Tv...> *_query_res;
};

CPPDB_NAMESPACE_END

#include "row.tcc"

#endif	/* ROW_HPP */

