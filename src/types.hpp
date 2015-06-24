/*
 * \file types.hpp
 * \author Andrew Kubera
 * \date January 6, 2014, 7:17 PM
 */

#pragma once

#include <typeinfo>
#include <stdint.h>
#include "namespace_macros.h"

CPPDB_NAMESPACE_BEGIN

// type for ports (IP)
typedef unsigned short port_t;

// status
typedef short status_t;

//
// SQL types
//
typedef int8_t  SQLByte_t;
typedef char    SQLChar_t;

typedef int16_t SQLInt_t;
typedef uint64_t SQLULong_t;

typedef float   SQLSingle_t;
typedef double  SQLDouble_t;

CPPDB_NAMESPACE_END
