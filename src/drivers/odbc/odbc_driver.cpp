/*
 * File:   odbc_driver.cpp
 * Author: andrewkubera
 *
 * Created on January 16, 2014, 12:23 PM
 */

#include "odbc_driver.hpp"

#include "connection.hpp"

#define SQL_STAT_SUCCESS(s) ((s == SQL_SUCCESS) || (s == SQL_SUCCESS_WITH_INFO))

odbc_driver::odbc_driver()

{
    auto status = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_env);
    if ((status != SQL_SUCCESS) && (status != SQL_SUCCESS_WITH_INFO)) {
        std::cerr << "[odbc_driver::odbc_driver] " "ERROR : AllocHandle" << std::endl;
        throw std::exception();
    }
    status = SQLSetEnvAttr(_env, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, 0);
    if ((status != SQL_SUCCESS) && (status != SQL_SUCCESS_WITH_INFO)) {
        std::cerr << "[odbc_driver::odbc_driver] " "ERROR : SQLSetEnvAttr" << std::endl;
        SQLFreeHandle(SQL_HANDLE_ENV, _env);
        throw std::exception();
    }

    status = SQLAllocHandle(SQL_HANDLE_DBC, _env, &_hdbc);

if (!SQL_SUCCEEDED(status))
{
  extract_error("SQLAllocHandle for dbc", _env, SQL_HANDLE_ENV);
  exit(1);
}


}

odbc_driver::odbc_driver(const odbc_driver& orig)
{
}

odbc_driver::~odbc_driver()
{
    SQLDisconnect(_hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, _env);
    SQLFreeHandle(SQL_HANDLE_DBC, _hdbc);
}

cppdb::status_t
odbc_driver::Connect(const std::string& host, const std::string& database, cppdb::port_t port, const std::string& username, const std::string& password)
{

    SQLRETURN status = SQLConnect(_hdbc,
            (SQLCHAR *)host.c_str(), (SQLSMALLINT)host.size(),
        (SQLCHAR *)username.c_str(), (SQLSMALLINT)username.size(),
        (SQLCHAR *)password.c_str(), (SQLSMALLINT)password.size());

    std::cout << "SQLConnect " << status << "\n";
    if (SQL_STAT_SUCCESS(status)) {
        return 0;
    }
    
   //  SQLError(
//       SQLHENV henv,                   /* 32-bit input */
//   SQLHDBC hdbc,                   /* 32-bit input */
//   SQLHSTMT hstmt,                 /* 32-bit input */
//   SQLCHAR *Sqlstate,              /* pointer to char* output -- char[5+1] */
//   SQLINTEGER *NativeError,        /* pointer to 32-bit output */
//   SQLCHAR *MessageText,           /* pointer to char* output */
//   SQLSMALLINT BufferLength,       /* 16-bit input */
//   SQLSMALLINT *TextLength         /* pointer to 16-bit output */
//   );


    // create statement handle
    SQLHSTMT hstmt = nullptr;
    // allocate space for the statment
    SQLAllocStmt(_hdbc, &hstmt);

    SQLCHAR Sqlstate[6];
    SQLINTEGER NativeError {0};
    SQLCHAR MessageText[1024];
    SQLSMALLINT TextLength {0};
 SQLError( _env, _hdbc,
          hstmt,
          Sqlstate,      
          &NativeError, 
  MessageText,    
  sizeof(MessageText),
  &TextLength);
    
    std::cout << "Error : " << MessageText << "\n";
    
    
    
    
    
    
    extract_error("SQLConnect", _env, SQL_HANDLE_ENV);

    // SQL_ERROR, SQL_INVALID_HANDLE, or SQL_STILL_EXECUTING
    return (cppdb::status_t)status;
}

void
odbc_driver::Query()
{
    // create statement handle
    SQLHSTMT stmt = nullptr;
    // allocate space for the statment
    SQLAllocStmt(_hdbc, &stmt);


    // buffers for returns
    SQLLEN err, id;
    char buffer[200];

    // TODO : Variadic template this function
    BindColumn<cppdb::SQLChar_t>(stmt, 1, &buffer, sizeof (buffer), &err);
    BindColumn<cppdb::SQLULong_t>(stmt, 2, &id, sizeof (id), &err);

    SQLCHAR qry_str[] = "SELECT whatever FROM wherever";
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

    SQLFreeStmt(stmt, SQL_DROP);
}

cppdb::status_t
odbc_driver::Disconnect()
{
    SQLRETURN status = SQLDisconnect(_hdbc);
    if (SQL_STAT_SUCCESS(status)) {
        return 0;
    }
    return 1;
}

cppdb::Driver*
create_driver()
{
  return new odbc_driver();
}

void
destroy_driver(cppdb::Driver* driver) {
  delete driver;
}
