/* 
 * File:   query.tcc
 * Author: andrewkubera
 *
 * Created on January 8, 2014, 5:35 PM
 */

#pragma once

#ifndef QUERY_HPP
#warning Including 'query.tcc' directly! You must only include query.hpp
#endif

#include "../cppdb.hpp"

CPPDB_NAMESPACE_BEGIN

template <typename... _Tv>
Query<_Tv>::Query() {
}

template <typename... _Tv>
Query<_Tv>::Query(const Query<_Tv>& orig) {
}

template <typename... _Tv>
Query<_Tv>::~Query() {
}

template <typename... _Tv>
QueryResult<_Tv...>
Query<_Tv>::Exec(cppdb::Connection) {
    auto res;
    return res;
}


CPPDB_NAMESPACE_END
