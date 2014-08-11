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
        
        typedef std::pair<SQLSMALLINT,SQLHANDLE> SQLEXCEPTION;        
        
        static DBConnection* globalDBConnection();
        
        void connect( const std::string& source, const std::string& user, const std::string& pwd );
        void disconnect();
        bool isConnected() { return connected; }
        // If table "tableName" doesn't exist a pointer to an empty
        // vector of strings will be returned.
        std::vector<std::string>* retrieveTableSchema( const std::string& tableName );
        ~DBConnection();
        
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

