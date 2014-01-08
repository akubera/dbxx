/* 
 * File:   query.hpp
 * Author: andrewkubera
 * 
 * Created on January 8, 2014, 5:35 PM
 */

#pragma once

#ifndef QUERY_HCC
#define	QUERY_HCC
#endif

#include "../cppdb.hpp"
#include "../connection.hpp"

#include "query_result.hpp"

CPPDB_NAMESPACE_BEGIN

template <typename... _Tv>
class Query {
public:
    Query();
    Query(const Query& orig);
    virtual ~Query();
    
    QueryResult<_Tv...> Exec(cppdb::Connection);

protected:

};



CPPDB_NAMESPACE_END

// include the templates
#include "query.tcc"
