/*
 * File:   orm.hpp
 * Author: andrewkubera
 *
 * Created on January 27, 2014, 11:30 AM
 */

#ifndef ORM_HPP
#define	ORM_HPP

#include "cppdb.hpp"
#include "query/query.hpp"

#include <map>
#include <tuple>

CPPDB_NAMESPACE_BEGIN

class ORM
{
public:
    ORM();
    ORM(const ORM& orig);
    virtual ~ORM();

    template <typename... Tv>
    ORM(cppdb::Row<Tv...>&);

    int save();

    template <typename... Tv>
    cppdb::Query<Tv...> create_table(bool if_not_exist = true);

protected:
    ORM* _orm;

    void bind(const std::string& name, void*ptr) {_field_to_ptr[name] = ptr;};

private:
    std::map<std::string, void*> _field_to_ptr;

};

CPPDB_NAMESPACE_END

// include the templates
#include "orm.tcc"

#endif	/* ORM_HPP */

