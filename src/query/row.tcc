/* 
 * File:   row.tcc
 * Author: andrewkubera
 * 
 * Created on January 8, 2014, 5:48 PM
 */


#include "../cppdb.hpp"

#ifndef ROW_HPP
#warning Including 'row.tcc' directly! You must only include row.hpp
#endif

CPPDB_NAMESPACE_BEGIN

template <typename... _Tv>
Row<_Tv...>::Row():
  _query_res(nullptr)
{
}

template <typename... _Tv>
Row<_Tv...>::Row(QueryResult<_Tv...>* source):
  _query_res(source)
{

}

template <typename... _Tv>
Row<_Tv...>::Row(const Row& orig)
{
}

template <typename... _Tv>
Row<_Tv...>::~Row()
{
}

template <typename... _Tv>
Row<_Tv...>
Row<_Tv...>::EmptyRow()
{
  Row < _Tv...> result;
  result._empty = true;
  return result;
}

CPPDB_NAMESPACE_END
