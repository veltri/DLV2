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

#include "DBConnection.h"
#include "ErrorMessage.h"
#include "Assert.h"
#include <cstring>

using namespace std;
using namespace DLV2::DB;

// Initialize singleton
DBConnection* DBConnection::instance = NULL;

DBConnection* 
DBConnection::globalDBConnection() 
{
    if( instance == NULL )
    {
        instance = new DBConnection();
    }
    return instance;
}

DBConnection::DBConnection():
        hEnv(NULL),
        hDBc(NULL),
        connected(false)
{
}

DBConnection::DBConnection(
    const DBConnection& dbc):
        source(dbc.source),
        pwd(dbc.pwd),
        user(dbc.user),
        hEnv(dbc.hEnv),
        hDBc(dbc.hDBc),
        connected(dbc.connected)
{
}

DBConnection::~DBConnection()
{
}

void
DBConnection::connect(
    const string& src,
    const string& usr,
    const string& pw )
{
    assert_msg( !connected, "You are already connected to a datasource." );
    source = src;
    user = usr;
    pwd = pw;
    string sourceString;
    sourceString.append("DSN=").append(source).
        append(";UID=").append(user).
        append(";PWD=").append(pwd).append(";");
    
    SQLRETURN retCode;
    try 
    {
        // Allocate environment handle
        retCode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLEXCEPTION(SQL_HANDLE_ENV,hEnv);

        // Set the ODBC version environment attribute
        retCode = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0); 
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLEXCEPTION(SQL_HANDLE_ENV,hEnv);

        // Allocate connection handle
        retCode = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDBc); 
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLEXCEPTION(SQL_HANDLE_DBC,hDBc);

        // Set login timeout to 5 seconds
        SQLSetConnectAttr(hDBc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

        // Connect to the datasource
        retCode = SQLDriverConnect(
            hDBc, 
            NULL, 
            (SQLCHAR*)sourceString.c_str(), 
            sourceString.size(),
            NULL,
            0, 
            NULL,
            SQL_DRIVER_NOPROMPT);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLEXCEPTION(SQL_HANDLE_DBC,hDBc);
        
        connected = true;
    /*    
        int row = 0;
        // Number of columns in result-set
        SQLSMALLINT columns; 
        // Retrieve table dogs' rows
        SQLExecDirect(hStmt,(SQLCHAR*)"SELECT * FROM dogs",SQL_NTS);
        SQLNumResultCols(hStmt, &columns);
		
        // Loop through the rows in the result-set
        while (SQL_SUCCEEDED(retCode = SQLFetch(hStmt))) 
        {
            SQLUSMALLINT i;
            cout << "Row " << row++ << endl;
            // Loop through the columns
            for (i = 1; i <= columns; i++) 
            {
                SQLLEN indicator;
                char buf[512];
                // Retrieve column data as a string
                retCode = SQLGetData(hStmt, i, SQL_C_CHAR,buf, sizeof(buf), &indicator);
                if (SQL_SUCCEEDED(retCode)) 
                {
                    // Handle null columns
                    if (indicator == SQL_NULL_DATA) 
                        strcpy(buf, "NULL");
                        
                    cout << "  Column " << i << " : " << buf << endl;
                }
            }
        }
        if (hStmt) { 
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            hStmt = NULL; 
        }
     */
    }
    catch(SQLEXCEPTION& exception)
    {
	SQLSMALLINT i = 1; 
        SQLSMALLINT MsgLen;
	SQLINTEGER NativeError;
	SQLCHAR SqlState[6];
        SQLCHAR Msg[SQL_MAX_MESSAGE_LENGTH];
	retCode = SQLGetDiagRec(exception.first, exception.second, i, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen);
	if( retCode == SQL_SUCCESS )
        {
            cerr << Msg << endl;
            //ErrorMessage::errorGeneric(string(Msg));
            exit(0);
        }
    }
    catch(...)
    {
    }
}

void
DBConnection::disconnect()
{
    assert_msg( connected, "You have to first connect to a datasource." );
    // Free handles, and disconnect.   
    if (hDBc) { 
        SQLDisconnect(hDBc);
        connected = false;
        SQLFreeHandle(SQL_HANDLE_DBC, hDBc);
        hDBc = NULL; 
    }
    if (hEnv) { 
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        hEnv = NULL; 
    }
    if( instance != NULL )
        delete instance;
}

void
DBConnection::setAutoCommit( 
    bool autoCommit )
{
    assert_msg( connected, "You have to first connect to a datasource." );
    if( autoCommit )
        SQLSetConnectAttr(hDBc,SQL_ATTR_AUTOCOMMIT,(SQLPOINTER)SQL_AUTOCOMMIT_ON,0);
    else
        SQLSetConnectAttr(hDBc,SQL_ATTR_AUTOCOMMIT,(SQLPOINTER)SQL_AUTOCOMMIT_OFF,0);
}

void
DBConnection::executeSQLStatement(
    const string& sql )
{
    assert_msg( connected, "You have to first connect to a datasource." );
    SQLRETURN retCode;
    SQLHSTMT hStmt = 0;
    try
    {
        // Allocate statement handle
        SQLAllocHandle(SQL_HANDLE_STMT, hDBc, &hStmt);
        retCode = SQLExecDirect(hStmt,(SQLCHAR*)sql.c_str(),SQL_NTS);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLEXCEPTION(SQL_HANDLE_STMT,hStmt);
    }
    catch(SQLEXCEPTION& exception)
    {
	SQLSMALLINT i = 1; 
        SQLSMALLINT MsgLen;
	SQLINTEGER NativeError;
	SQLCHAR SqlState[6];
        SQLCHAR Msg[SQL_MAX_MESSAGE_LENGTH];
	retCode = SQLGetDiagRec(exception.first, exception.second, i, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen);
	if( retCode == SQL_SUCCESS )
        {
            cerr << Msg << endl;
            //ErrorMessage::errorGeneric(string(Msg));
            exit(0);
        }
    }
    if (hStmt) { 
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        hStmt = NULL; 
    }
}

void
DBConnection::commit()
{
    assert_msg( connected, "You have to first connect to a datasource." );
    SQLEndTran(SQL_HANDLE_DBC,hDBc,SQL_COMMIT);
}

void
DBConnection::rollback()
{
    assert_msg( connected, "You have to first connect to a datasource." );
    SQLEndTran(SQL_HANDLE_DBC,hDBc,SQL_ROLLBACK);    
}

vector<string>*
DBConnection::retrieveTableSchema(
    const std::string& tableName ) 
{
    assert_msg( connected, "You have to first connect to a datasource." );
    vector<string>* attributesList = new vector<string>();
    SQLRETURN retCode;
    SQLHSTMT hStmt = 0;
    try
    {
        // Allocate statement handle
        SQLAllocHandle(SQL_HANDLE_STMT, hDBc, &hStmt);
        retCode = SQLColumns(hStmt, NULL, 0, NULL, 0, (SQLCHAR*)tableName.c_str(), SQL_NTS, NULL, 0);
        if( SQL_SUCCEEDED(retCode) )
        {
            // Declare buffers for result set data
            unsigned STR_LEN = 128 + 1;
            char szColumnName[STR_LEN];
            //SQLCHAR szTypeName[STR_LEN];
            // Declare buffers for bytes available to return
            SQLLEN cbColumnName;
            //SQLINTEGER cbTypeName;
            // Bind columns in result set to buffers
            SQLBindCol(hStmt, 4, SQL_C_CHAR, szColumnName, STR_LEN, &cbColumnName);
            //SQLBindCol(hstmt, 6, SQL_C_CHAR, szTypeName, STR_LEN, &cbTypeName);
            while (SQL_SUCCEEDED(retCode = SQLFetch(hStmt))) 
            {            
//                cout << "Attribute name: " << szColumnName << endl;
                attributesList->push_back(string(szColumnName));
            }
            // If attributeList is empty, table "tableName" doesn't exist.
        }
        else 
            throw SQLEXCEPTION(SQL_HANDLE_STMT,hStmt);
    }
    catch(SQLEXCEPTION& exception)
    {
	SQLSMALLINT i = 1; 
        SQLSMALLINT MsgLen;
	SQLINTEGER NativeError;
	SQLCHAR SqlState[6];
        SQLCHAR Msg[SQL_MAX_MESSAGE_LENGTH];
	retCode = SQLGetDiagRec(exception.first, exception.second, i, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen);
	if( retCode == SQL_SUCCESS )
        {
            cerr << Msg << endl;
            //ErrorMessage::errorGeneric(string(Msg));
            exit(0);
        }
    }
    if (hStmt) { 
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        hStmt = NULL; 
    }
    return attributesList;
}

