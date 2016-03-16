/*
 *
 *  Copyright 2014 Mario Alviano, Carmine Dodaro, Francesco Ricca and
 *                 Pierfrancesco Veltri.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

/* 
 * File:   DBConnection.h
 * Author: pierfrancesco
 *
 * Created on 5 agosto 2014, 18.27
 */

#ifndef DBCONNECTION_H
#define	DBCONNECTION_H

#ifdef STATIC
#else
#include <sql.h>
#include <sqlext.h>
#endif

#include <string>
#include <vector>
#include "Constants.h"

namespace DLV2{ namespace DB{

#ifdef STATIC
class DBConnection {
 public:
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
     static DBConnection* globalDBConnection(){};

     ~DBConnection(){};

     void connect( const std::string& source, const std::string& user, const std::string& pwd ){};
     void disconnect(){};
     bool isConnected() const {  }
     void setAutoCommit( bool autoCommit ) const{};
     void executeSQLStatement( const std::string& sql ) const{};
     void commit() const{};
     void rollback() const{};

     /* DataHandler */

     /** Provide the name of the table matching the input pair <predName,arity>
      * by querying meta table "tableNames" that must be present in the working
      * database. If a matching table doesn't exist, it will be created and
      * its name will be stored in table "tableNames".
      * @param predName The predicate's name.
      * @param arity The predicate's arity.
      * @param outTableName The name of the matching table.
      * @return a pointer to a dinamically instantiated string containing
      * the name of the matching table; the caller will be responsible of
      * the destruction of that vector.
      */
     std::string* retrieveTableName(
         const std::string& predName,
         unsigned arity ) const{};
     /** Retrive the attributes' names of table <tableName>.
      * Notice that, table <tableName> must exist.
      * @param tableName The name of the table to be investigated.
      * @param nAttributes USELESS
      * @return a pointer to a dinamically instantiated vector of strings,
      * the caller will be responsible of the destruction of that vector.
      */
     std::vector<std::string>* retrieveTableSchema(
         const std::string& tableName,
         unsigned nAttributes ) const{};
     /** Retrieve the next valid execution timestamp.
      * @return such a timestamp
      */
     Timestamp retrieveNextExecutionTimestamp(){};
     /** Retrieve the next available timestamp to insert
      * new tuples to table tableName.
      * @param tableName The name of the table to be investigated
      * @return the next available timestamp for wich new
      * tuples can be added to table tableName.
      */
     Timestamp retrieveNextTableTimestamp(
             const std::string& tableName ) const{};
#pragma GCC diagnostic pop

 private:
 };
#else
    class DBConnection {
    public:
        typedef std::pair<SQLSMALLINT,SQLHANDLE> SQLException;

        static DBConnection* globalDBConnection();

        ~DBConnection();

        void connect( const std::string& source, const std::string& user, const std::string& pwd );
        void disconnect();
        bool isConnected() const { return connected; }
        void setAutoCommit( bool autoCommit ) const;
        void executeSQLStatement( const std::string& sql ) const;
        void commit() const;
        void rollback() const;

        /* DataHandler */

        /** Provide the name of the table matching the input pair <predName,arity>
         * by querying meta table "tableNames" that must be present in the working
         * database. If a matching table doesn't exist, it will be created and
         * its name will be stored in table "tableNames".
         * @param predName The predicate's name.
         * @param arity The predicate's arity.
         * @param outTableName The name of the matching table.
         * @return a pointer to a dinamically instantiated string containing
         * the name of the matching table; the caller will be responsible of
         * the destruction of that vector.
         */
        std::string* retrieveTableName(
            const std::string& predName,
            unsigned arity ) const;
        /** Retrive the attributes' names of table <tableName>.
         * Notice that, table <tableName> must exist.
         * @param tableName The name of the table to be investigated.
         * @param nAttributes USELESS
         * @return a pointer to a dinamically instantiated vector of strings,
         * the caller will be responsible of the destruction of that vector.
         */
        std::vector<std::string>* retrieveTableSchema(
            const std::string& tableName,
            unsigned nAttributes ) const;
        /** Retrieve the next valid execution timestamp.
         * @return such a timestamp
         */
        Timestamp retrieveNextExecutionTimestamp();
        /** Retrieve the next available timestamp to insert
         * new tuples to table tableName.
         * @param tableName The name of the table to be investigated
         * @return the next available timestamp for wich new
         * tuples can be added to table tableName.
         */
        Timestamp retrieveNextTableTimestamp(
                const std::string& tableName ) const;

    private:

        static DBConnection* instance;

        DBConnection();
        DBConnection( const DBConnection& dbc );

        std::string source;
        std::string pwd;
        std::string user;
        SQLHENV hEnv;
        SQLHDBC hDBc;
        bool connected;

        /* DataHandler */

        Timestamp currentExecutionTimestamp;

    };
#endif

};};

#endif	/* DBCONNECTION_H */

