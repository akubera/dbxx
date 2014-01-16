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

/*template <typename T>
#void
#odbc_driver::BindColumn(SQLHSTMT stmt, SQLUSMALLINT col_num, SQLPOINTER  target_val_ptr, SQLLEN buffsize, SQLLEN * strlen) {
//   SQLBindCol(stmt, 1, SQL_C_CHAR, target_val_ptr, buffsize, strlen);
}*/


template<>
void
odbc_driver::BindColumn<cppdb::SQLChar_t> (SQLHSTMT stmt, SQLUSMALLINT col_num, SQLPOINTER  target_val_ptr, SQLLEN buffsize, SQLLEN * strlen) {
    SQLBindCol(stmt, col_num, SQL_C_CHAR, target_val_ptr, buffsize, strlen);
}

template<>
void
odbc_driver::BindColumn<cppdb::SQLULong_t> (SQLHSTMT stmt, SQLUSMALLINT col_num, SQLPOINTER  target_val_ptr, SQLLEN buffsize, SQLLEN * strlen) {
    SQLBindCol(stmt, col_num, SQL_C_ULONG, target_val_ptr, buffsize, strlen);
}
