/*
 * File:   odbc_driver.tcc
 * Author: andrewkubera
 *
 * Created on January 16, 2014, 4:44 PM
 */

#include "odbc_driver.hpp"

template<>
void
odbc_driver::BindColumn<cppdb::SQLChar_t> (SQLHSTMT stmt,
                                    SQLUSMALLINT col_num,
                              SQLPOINTER  target_val_ptr,
                                         SQLLEN buffsize,
                                         SQLLEN * strlen)
{
    SQLBindCol(stmt, col_num, SQL_C_CHAR, target_val_ptr, buffsize, strlen);
}

template<>
void
odbc_driver::BindColumn<cppdb::SQLULong_t>(SQLHSTMT stmt,
                                    SQLUSMALLINT col_num,
                               SQLPOINTER target_val_ptr,
                                         SQLLEN buffsize,
                                         SQLLEN * strlen)
{
    SQLBindCol(stmt, col_num, SQL_C_ULONG, target_val_ptr, buffsize, strlen);
}
