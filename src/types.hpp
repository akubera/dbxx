/* 
 * File:   types.hpp
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 7:17 PM
 */

#pragma once

#include <typeinfo>

namespace cppdb
{
    // type for ports (IP)
    typedef unsigned short port_t;

    //
    // SQL types
    //
    typedef char    SQLByte_t;
    typedef int16_t SQLInt_t;
    typedef float   SQLSingle_t;
    typedef double  SQLDouble_t;

}
