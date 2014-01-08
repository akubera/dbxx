/* 
 * File:   row.hpp
 * Author: andrewkubera
 *
 * Created on January 8, 2014, 5:48 PM
 */

#ifndef ROW_HPP
#define	ROW_HPP

#include "../cppdb.hpp"

CPPDB_NAMESPACE_BEGIN

/**
 * Row is a single result element from an executed query
 */
template <typename... _Tv>
class Row {
public:
    Row();
    Row(const Row& orig);
    virtual ~Row();

protected:

};

CPPDB_NAMESPACE_END

#include "row.tcc"

#endif	/* ROW_HPP */

