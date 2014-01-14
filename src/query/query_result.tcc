/* 
 * File:   query_result.cpp
 * Author: andrewkubera
 * 
 * Created on January 8, 2014, 5:51 PM
 */

#include "query_result.hpp"

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
QueryResult<_Tv...>::begin()
{
    Row<_Tv...> result(this, 0);
    return result;
}

template <typename... _Tv>
Row<_Tv...>
QueryResult<_Tv...>::end()
{
    return Row< _Tv...>::EmptyRow();
}



CPPDB_NAMESPACE_END

