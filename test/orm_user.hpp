/*
 * File:   orm_user.hpp
 * Author: andrewkubera
 *
 * Created on January 27, 2014, 11:57 AM
 */

#pragma once

#include "../src/orm.hpp"

#include <array>

typedef std::array<char, 40> username_t;

class user : public cppdb::ORM  {
    user() {
        bind("id", &id);
        bind("username", &username);
    };

    ~user(){};

protected:
    // user id
    int id;

    // username
    username_t username;

};



