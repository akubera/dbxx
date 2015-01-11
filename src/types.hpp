/*
 * File:   types.hpp
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 7:17 PM
 */

#pragma once

#include <typeinfo>
#include <stdint.h>

#define CPPDB_NAMESPACE_BEGIN namespace cppdb {
#define CPPDB_NAMESPACE_END }

CPPDB_NAMESPACE_BEGIN

// type for ports (IP)
typedef unsigned short port_t;

// status
typedef short status_t;

//
// SQL types
//
typedef char    SQLByte_t;
typedef char    SQLChar_t;

typedef int16_t SQLInt_t;
typedef unsigned long int SQLULong_t;

typedef float   SQLSingle_t;
typedef double  SQLDouble_t;

CPPDB_NAMESPACE_END
