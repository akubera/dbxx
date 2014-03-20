/*
 * File:   exceptions.hpp
 * Author: andrewkubera
 *
 * Created on March 20, 2014, 5:21 PM
 */

#pragma once

#include <exception>

CPPDB_NAMESPACE_BEGIN

class NoDriverException : public std::exception {};

CPPDB_NAMESPACE_END
