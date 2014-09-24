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

#include <sql.h>
#include <sqlext.h>
#include <string>
#include <vector>

namespace DLV2{ namespace DB{

    class DBConnection {
    public:
        typedef std::pair<SQLSMALLINT,SQLHANDLE> SQLException;
        
        static DBConnection* globalDBConnection();
        
        ~DBConnection();
        
        void connect( const std::string& source, const std::string& user, const std::string& pwd );
        void disconnect();
        bool isConnected() { return connected; }
        void setAutoCommit( bool autoCommit );
        void executeSQLStatement( const std::string& sql );
        void commit();
        void rollback();
        
        /* MetadataHandler */
        
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
            unsigned arity );
        /** Retrive the attributes' names of table <tableName>. 
         * Notice that, table <tableName> must exist.
         * @param tableName The name of the table to be investigated.
         * @param nAttributes USELESS
         * @return a pointer to a dinamically instantiated vector of strings, 
         * the caller will be responsible of the destruction of that vector.
         */ 
        std::vector<std::string>* retrieveTableSchema( 
            const std::string& tableName,
            unsigned nAttributes );
        
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
    };
    
};};

#endif	/* DBCONNECTION_H */

