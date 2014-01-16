/*
 * File:   odbc_driver.hpp
 * Author: andrewkubera
 *
 * Created on January 16, 2014, 12:23 PM
 */

#pragma once

#include "../../driver.hpp"
#include "../../types.hpp"

#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

class odbc_driver : public cppdb::Driver {
public:
    odbc_driver();
    odbc_driver(const odbc_driver& orig);
    virtual ~odbc_driver();

    void Disconnect();
    void Query();

protected:
    template <typename T>
    void BindColumn(SQLHSTMT stmt, SQLUSMALLINT col_num, SQLPOINTER  target_val_ptr, SQLLEN buffsize, SQLLEN * strlen);

protected:
    // sql environment
    SQLHENV _env;

    // sql connection
    SQLHDBC _hdbc;

    // sql status
    char  _sql_stat[10];

};

extern "C" cppdb::Driver* create_driver();
extern "C" void destroy_driver(cppdb::Driver* driver);

// include template implementations
#include "obdc_driver.tcc"