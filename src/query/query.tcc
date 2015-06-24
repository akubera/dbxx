/* 
 * File:   query.tcc
 * Author: andrewkubera
 *
 * Created on January 8, 2014, 5:35 PM
 */

#ifndef QUERY_HPP
#warning Including 'query.tcc' directly! You must only include query.hpp
#endif

#include "../cppdb.hpp"
#include "../connection.hpp"

#include <sstream>

CPPDB_NAMESPACE_BEGIN

template <typename... _Tv>
Query<_Tv...>::Query()
{
}

template <typename... _Tv>
Query<_Tv...>::Query(const Query<_Tv...>& orig)
{
}

template <typename... _Tv>
Query<_Tv...>::~Query()
{
}

template <typename... _Tv>
QueryResult<_Tv...>
Query<_Tv...>::Exec(cppdb::Connection&)
{
  QueryResult < _Tv...> res;
  return res;
}

template <typename... _Tv>
Query<_Tv...>&
Query<_Tv...>::select(const std::string& x)
{
  return *this;
};

template <typename... _Tv>
Query<_Tv...>&
Query<_Tv...>::from(const std::string&)
{
  return *this;
};

template <typename... _Tv>
Query<_Tv...>&
Query<_Tv...>::where(const std::string&)
{
  return *this;
};

template <typename... _Tv>
std::string
Query<_Tv...>::toString()
{
  std::stringstream ss;
  
  ss << "QUERY <>";
  return ss.str();  
}



CPPDB_NAMESPACE_END
