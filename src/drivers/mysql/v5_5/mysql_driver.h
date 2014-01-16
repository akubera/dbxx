/*
 * File:   mysql_driver.h
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 9:42 PM
 */

#pragma once

#include <string>
#include <cstdlib>

#include <mysql.h>
#include "../../../driver.hpp"

class mysql_driver : public cppdb::Driver
{
public:
    mysql_driver();
    mysql_driver(const mysql_driver& orig);
    virtual ~mysql_driver();

    cppdb::status_t Connect(const std::string& host, const std::string& database, cppdb::port_t port, const std::string& username, const std::string& password);

    cppdb::status_t Disconnect();
    //

    void ExecQueryString(const std::string& query)
    {
        int err = mysql_real_query(_conn, query.c_str(), query.size());
        if (err) {
            // TODO : handle error
            std::cerr << "Error " << mysql_errno(_conn) << " : " << mysql_error(_conn) << std::endl;
            return;
        }
        // build the result
        // The number of columns for the most recent query on the connection.
        MYSQL_RES * result = mysql_store_result(_conn);

        // no rows were returned
        if (result == nullptr) {
            if (mysql_field_count(_conn) != 0) {
                // error
            }
            else {
                // succes
            }
        }

        // data returned - parse through the result
        else {
            std::vector < std::pair < std::string, size_t >> returned_field_info;
            // build field list
            size_t field_count = mysql_num_fields(result);
            MYSQL_FIELD *field_array = mysql_fetch_fields(result);

            for (auto i = 0; i < field_count; i++) {
                std::pair<std::string, size_t> field(field_array[i].name, field_array[i].length);
                returned_field_info.push_back(field);
            }

            std::vector<std::vector<std::string>> r;

            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                r.push_back(std::vector<std::string>(field_count));
                for (size_t i = 0; i < field_count; ++i) {
                    r.back()[i] = row[i];
                }
            }


            // finally, delete the result
            mysql_free_result(result);
        }
    };

    void GetTables(const std::string& match = "")
    {
        const char *wild = (match == "" ? nullptr : match.c_str());
        MYSQL_RES *tables = mysql_list_tables(_conn, wild);
        if (tables == nullptr) {
            // error
        }
        // TODO : Build result
        mysql_free_result(tables);
    }

    void GetFields(const std::string& table, const std::string& match = "")
    {
        const char *wild = (match == "" ? nullptr : match.c_str());
        MYSQL_RES *fields = mysql_list_fields(_conn, table.c_str(), wild);
        if (fields == nullptr) {
            // error
        }

        size_t field_cnt = mysql_num_fields(fields);
        for (auto i = 0; i < field_cnt; ++i) {
            MYSQL_FIELD *col = mysql_fetch_field_direct(fields, i);
            printf("Column %d: %s\n", i, col->name);
        }
        mysql_free_result(fields);
    }

protected:
    MYSQL *_conn;

    std::string _host;
    cppdb::port_t _port;

    std::string _username;
    std::string _password;
    std::string _database {""};

    MYSQL_RES *res;
    MYSQL_ROW row;
};
