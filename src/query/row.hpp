/*
 * File:   row.hpp
 * Author: andrewkubera
 *
 * Created on January 8, 2014, 5:48 PM
 */


#pragma once

// This is included to allow a check for row.tcc
#ifndef ROW_HPP
#define	ROW_HPP

#include "../cppdb.hpp"
#include "../types.hpp"

#include <memory>
#include <tuple>

CPPDB_NAMESPACE_BEGIN

/**
 * Row is a single result element from an executed query
 */
template <typename... _Tv>
class Row
{
public:
    Row();
    Row(std::shared_ptr<QueryResult<_Tv...>>);
    Row(const Row& orig);
    virtual ~Row();
    
    Row<_Tv...>& operator++();
    std::tuple<_Tv...> operator*();
    bool operator==(const Row<_Tv...>& rhs);

    static Row<_Tv...> EmptyRow();

protected:
    /**
     * Position index of row in query result
     */
    size_t _index {0};

    /**
     * An empty row which is used to denote the end of a query result
     */
    bool _empty {false};

    std::tuple<_Tv...> _data;

    std::shared_ptr<QueryResult<_Tv...>> _query_res;
};

CPPDB_NAMESPACE_END

#include "row.tcc"

#endif	/* ROW_HPP */

