/*
 * File:   odbc_driver.cpp
 * Author: andrewkubera
 *
 * Created on January 16, 2014, 12:23 PM
 */

#include "odbc_driver.hpp"

odbc_driver::odbc_driver()

{
    auto status = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_env);
    if ((status != SQL_SUCCESS) && (status != SQL_SUCCESS_WITH_INFO)) {
        std::cerr << "[odbc_driver::odbc_driver] " "ERROR : AllocHandle" << std::endl;
        throw std::exception();
    }
    status = SQLSetEnvAttr(_env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if ((status != SQL_SUCCESS) && (status != SQL_SUCCESS_WITH_INFO)) {
        std::cerr << "[odbc_driver::odbc_driver] " "ERROR : SQLSetEnvAttr" << std::endl;
        SQLFreeHandle(SQL_HANDLE_ENV, _env);
        throw std::exception();
    }

}

odbc_driver::odbc_driver(const odbc_driver& orig) {
}

odbc_driver::~odbc_driver() {
    SQLFreeHandle(SQL_HANDLE_ENV, _env);
    SQLFreeHandle(SQL_HANDLE_DBC, _hdbc);
}

void
odbc_driver::Query() {
    // create statement handle
    SQLHSTMT stmt = nullptr;

    // buffers for returns
    SQLLEN err, id;
    char buffer[200];

    // TODO : Variadic template this function
    BindColumn<cppdb::SQLChar_t>(stmt, 1, &buffer, sizeof(buffer), &err);
    BindColumn<cppdb::SQLULong_t>(stmt, 2, &id, sizeof(id), &err);

    SQLCHAR qry_str[] = "SELECT whatever FROM whereever";
    SQLCHAR *qury = qry_str;

    SQLRETURN status = SQLExecDirect(stmt, qury, SQL_NTS);
    switch (status) {
    case SQL_ERROR:
    case SQL_INVALID_HANDLE:
//    case SQL_PARAM_DATA_AVAILABLE:
    case SQL_NO_DATA:
    case SQL_NEED_DATA:
    case SQL_STILL_EXECUTING:

    case SQL_SUCCESS_WITH_INFO:
        // handle info and drop down
    case SQL_SUCCESS:
        break;
    }
}

void
odbc_driver::Disconnect() {
  SQLDisconnect(_hdbc);
}



