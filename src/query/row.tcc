/*
 * \file query/row.tcc
 * \author Andrew Kubera
 * \date January 8, 2014, 5:48 PM
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
Row<_Tv...>::Row(std::shared_ptr<QueryResult<_Tv...>> source):
  _query_res(source)
{

}

template <typename... _Tv>
Row<_Tv...>::Row(const Row<_Tv...>& orig):
  _index(orig._index),
  _query_res(orig._query_res)
{
}

template <typename... _Tv>
Row<_Tv...>::~Row()
{
  _query_res.reset();
}

template <typename... _Tv>
Row<_Tv...>
Row<_Tv...>::EmptyRow()
{
  Row<_Tv...> result;
  result._empty = true;
  return result;
}

template <typename... _Tv>
Row<_Tv...>&
Row<_Tv...>::operator++()
{
  _index++;
  _data = _query_res->GetAsTuple(_index);
  return *this;
}


template <typename... _Tv>
std::tuple<_Tv...>
Row<_Tv...>::operator*() {
  return _data;
}

template <typename... _Tv>
bool
Row<_Tv...>::operator==(const Row<_Tv...>& rhs) {
  // TODO : Choose whether or not two different empty rows with different
  bool empty = (_empty && rhs._empty);
  bool res = (rhs._index == _index) && (rhs._query_res == _query_res);
  return empty || res;
}


CPPDB_NAMESPACE_END
