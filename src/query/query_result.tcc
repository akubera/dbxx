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
QueryResult::QueryResult()
{
}

QueryResult::QueryResult(const QueryResult& orig)
{
}

QueryResult::~QueryResult()
{
}

CPPDB_NAMESPACE_END

