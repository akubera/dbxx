/* 
 * File:   query_result.hpp
 * Author: andrewkubera
 *
 * Created on January 8, 2014, 5:51 PM
 */

#ifndef QUERY_RESULT_HPP
#define	QUERY_RESULT_HPP

#include "../cppdb.hpp"

CPPDB_NAMESPACE_BEGIN

template <typename... _Tv>
class QueryResult
{
public:
    QueryResult();
    QueryResult(const QueryResult& orig);
    virtual ~QueryResult();

protected:

};

CPPDB_NAMESPACE_END

#endif	/* QUERY_RESULT_HPP */

