/*
 * \file exceptions.hpp
 * \author Andrew Kubera
 * \date March 20, 2014, 5:21 PM
 */

#pragma once

#include <exception>
#include "namespace_macros.h"

CPPDB_NAMESPACE_BEGIN

class NoDriverException : public std::exception {};

CPPDB_NAMESPACE_END
