/* 
 * File:   query_result.cpp
 * Author: andrewkubera
 * 
 * Created on January 8, 2014, 5:51 PM
 */

#include "query_result.hpp"
#include "query.hpp"

#ifndef QUERY_RESULT_HPP
#warning Including 'query_result.tcc' directly! You must only include query_result.hpp
#endif

CPPDB_NAMESPACE_BEGIN

template <typename... _Tv>
QueryResult<_Tv...>::QueryResult()
{
}

template <typename... _Tv>
QueryResult<_Tv...>::QueryResult(const QueryResult& orig)
{
}

template <typename... _Tv>
QueryResult<_Tv...>::~QueryResult()
{
}

template <typename... _Tv>
Row<_Tv...>
QueryResult<_Tv...>::getRow(size_t rownumber)
{
  Row<_Tv...> result(this);
  return result;
}

template <typename... _Tv>
Row<_Tv...>
QueryResult<_Tv...>::begin()
{
  return getRow(0);
}

template <typename... _Tv>
Row<_Tv...>
QueryResult<_Tv...>::end()
{
  return Row<_Tv...>::EmptyRow();
}

template <typename... _Tv>
std::tuple<_Tv...>
QueryResult<_Tv...>::GetAsTuple(size_t index)
{
  return std::tuple<_Tv...>();
}




CPPDB_NAMESPACE_END

