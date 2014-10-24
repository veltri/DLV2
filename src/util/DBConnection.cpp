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
#include "Constants.h"
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
    currentExecutionTimestamp = 0;
}

DBConnection::DBConnection(
    const DBConnection& dbc):
        source(dbc.source),
        pwd(dbc.pwd),
        user(dbc.user),
        hEnv(dbc.hEnv),
        hDBc(dbc.hDBc),
        connected(dbc.connected),
        currentExecutionTimestamp(dbc.currentExecutionTimestamp)
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
            throw SQLException(SQL_HANDLE_ENV,hEnv);

        // Set the ODBC version environment attribute
        retCode = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0); 
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_ENV,hEnv);

        // Allocate connection handle
        retCode = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDBc); 
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_DBC,hDBc);

        // Set login timeout to 5 seconds
        retCode = SQLSetConnectAttr(hDBc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_DBC,hDBc);
        
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
            throw SQLException(SQL_HANDLE_DBC,hDBc);
        
        connected = true;
    }
    catch( SQLException& exception )
    {
        SQLSMALLINT i = 1;
        SQLSMALLINT MsgLen;
        SQLINTEGER NativeError;
        SQLCHAR SqlState[6];
        SQLCHAR Msg[SQL_MAX_MESSAGE_LENGTH];
        retCode = SQLGetDiagRec(exception.first, exception.second, i, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen);
        if( retCode == SQL_SUCCESS )
            ErrorMessage::errorDBConnection(Msg);
        else
            ErrorMessage::errorDBConnection("Unknown error");
    }
}

void
DBConnection::disconnect()
{
    assert_msg( connected, "You have to first connect to a datasource." );
    SQLRETURN retCode;
    try{
        // Free handles, and disconnect.   
        if (hDBc) { 
            retCode = SQLDisconnect(hDBc);
            if( !SQL_SUCCEEDED(retCode) )
                throw SQLException(SQL_HANDLE_DBC,hDBc);
            connected = false;
            
            retCode = SQLFreeHandle(SQL_HANDLE_DBC, hDBc);
            if( !SQL_SUCCEEDED(retCode) )
                throw SQLException(SQL_HANDLE_DBC,hDBc);
            hDBc = NULL; 
        }
        if (hEnv) { 
            retCode = SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
            if( !SQL_SUCCEEDED(retCode) )
                throw SQLException(SQL_HANDLE_DBC,hEnv);
            hEnv = NULL; 
        }
        if( instance != NULL )
            delete instance;
    }
    catch( SQLException& exception )
    {
        SQLSMALLINT i = 1;
        SQLSMALLINT MsgLen;
        SQLINTEGER NativeError;
        SQLCHAR SqlState[6];
        SQLCHAR Msg[SQL_MAX_MESSAGE_LENGTH];
        retCode = SQLGetDiagRec(exception.first, exception.second, i, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen);
        if( retCode == SQL_SUCCESS )
            ErrorMessage::errorDBConnection(Msg);
        else
            ErrorMessage::errorDBConnection("Unknown error");
    }
}

void
DBConnection::setAutoCommit( 
    bool autoCommit ) const
{
    assert_msg( connected, "You have to first connect to a datasource." );
    SQLRETURN retCode;
    try{
        if( autoCommit )
            retCode = SQLSetConnectAttr(hDBc,SQL_ATTR_AUTOCOMMIT,(SQLPOINTER)SQL_AUTOCOMMIT_ON,0);
        else
            retCode = SQLSetConnectAttr(hDBc,SQL_ATTR_AUTOCOMMIT,(SQLPOINTER)SQL_AUTOCOMMIT_OFF,0);
        
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_DBC,hDBc);
    }
    catch( SQLException& exception )
    {
        SQLSMALLINT i = 1;
        SQLSMALLINT MsgLen;
        SQLINTEGER NativeError;
        SQLCHAR SqlState[6];
        SQLCHAR Msg[SQL_MAX_MESSAGE_LENGTH];
        retCode = SQLGetDiagRec(exception.first, exception.second, i, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen);
        if( retCode == SQL_SUCCESS )
            ErrorMessage::errorDBConnection(Msg);
        else
            ErrorMessage::errorDBConnection("Unknown error");
    }    
}

void
DBConnection::executeSQLStatement(
    const string& sql ) const
{
    assert_msg( connected, "You have to first connect to a datasource." );
    SQLRETURN retCode;
    SQLHSTMT hStmt = 0;
    try
    {
        // Allocate statement handle
        retCode = SQLAllocHandle(SQL_HANDLE_STMT, hDBc, &hStmt);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hStmt);
        
        retCode = SQLExecDirect(hStmt,(SQLCHAR*)sql.c_str(),SQL_NTS);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hStmt);
        
        retCode = SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hStmt);
    }
    catch( SQLException& exception )
    {
        SQLSMALLINT i = 1;
        SQLSMALLINT MsgLen;
        SQLINTEGER NativeError;
        SQLCHAR SqlState[6];
        SQLCHAR Msg[SQL_MAX_MESSAGE_LENGTH];
        retCode = SQLGetDiagRec(exception.first, exception.second, i, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen);
        if( retCode == SQL_SUCCESS )
            ErrorMessage::errorDBConnection(Msg);
        else
            ErrorMessage::errorDBConnection("Unknown error");
    }
}

void
DBConnection::commit() const
{
    assert_msg( connected, "You have to first connect to a datasource." );
    SQLRETURN retCode;
    try
    {
        retCode = SQLEndTran(SQL_HANDLE_DBC,hDBc,SQL_COMMIT);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hDBc);
    }
    catch( SQLException& exception )
    {
        SQLSMALLINT i = 1;
        SQLSMALLINT MsgLen;
        SQLINTEGER NativeError;
        SQLCHAR SqlState[6];
        SQLCHAR Msg[SQL_MAX_MESSAGE_LENGTH];
        retCode = SQLGetDiagRec(exception.first, exception.second, i, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen);
        if( retCode == SQL_SUCCESS )
            ErrorMessage::errorDBConnection(Msg);
        else
            ErrorMessage::errorDBConnection("Unknown error");
    }    
}

void
DBConnection::rollback() const
{
    assert_msg( connected, "You have to first connect to a datasource." );
    SQLRETURN retCode;
    try
    {
        retCode = SQLEndTran(SQL_HANDLE_DBC,hDBc,SQL_ROLLBACK);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hDBc);
    }
    catch( SQLException& exception )
    {
        SQLSMALLINT i = 1;
        SQLSMALLINT MsgLen;
        SQLINTEGER NativeError;
        SQLCHAR SqlState[6];
        SQLCHAR Msg[SQL_MAX_MESSAGE_LENGTH];
        retCode = SQLGetDiagRec(exception.first, exception.second, i, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen);
        if( retCode == SQL_SUCCESS )
            ErrorMessage::errorDBConnection(Msg);
        else
            ErrorMessage::errorDBConnection("Unknown error");
    }    
}

string*
DBConnection::retrieveTableName(
    const std::string& predName,
    unsigned arity ) const
{
    assert_msg( connected, "You have to first connect to a datasource." );
    string* outTableName = new string();
    SQLRETURN retCode;
    SQLHSTMT hStmt = 0;
    try
    {
        // Allocate statement handle
        retCode = SQLAllocHandle(SQL_HANDLE_STMT, hDBc, &hStmt);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hStmt);

        // FIXME: sql code should not be included in this class.
        string tableNames(TABLE_NAMES);
        string sqlId = "SELECT id FROM "+tableNames+" WHERE name='"+predName+"' AND arity="+to_string(arity);
        retCode = SQLExecDirect(hStmt,(SQLCHAR*)sqlId.c_str(),SQL_NTS);

        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hStmt);

        // Declare buffers for result set data
        unsigned STR_LEN = 128 + 1;
        char szTableName[STR_LEN];
        // Declare buffers for bytes available to return
        SQLLEN cbTableName;
        // Bind columns in result set to buffers
        retCode = SQLBindCol(hStmt, 1, SQL_C_CHAR, szTableName, STR_LEN, &cbTableName);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hStmt);

        // There should be at most one record matching the input pair <predName,arity>.
        // If no matchings are found, create one.
        retCode = SQLFetch(hStmt);
        if( SQL_SUCCEEDED(retCode) )
        {
            outTableName->assign(szTableName);
            assert_msg( !SQL_SUCCEEDED(retCode = SQLFetch(hStmt)),
                "More than one table matches the input predicate" );
        }
        else if( retCode == SQL_NO_DATA )
        {
            // If such a matching does not exist,
            // insert a new record and create the matching table.

            // FIXME: at the moment we are not able to handle datatype mappings,
            // so we create only tables with string attributes.

            setAutoCommit(false);

            // The id of the table that is about to be added is built as follows:
            // <predName_COD>, where COD is the number of tables (included
            // in the working database) matching predicate predName.

            // Retrieve the number of tables matching the predicate name in input.
            // Notice that, this query has to be executed because there might be
            // a table matching predicate predName with a different arity.
            string sqlCount = "SELECT COUNT(*) FROM "+tableNames+" WHERE name='"+predName+"'";
            // Close the cursor.
            SQLCloseCursor(hStmt);
            retCode = SQLExecDirect(hStmt,(SQLCHAR*)sqlCount.c_str(),SQL_NTS);
            if( !SQL_SUCCEEDED(retCode) )
                throw SQLException(SQL_HANDLE_STMT,hStmt);

            SQLUSMALLINT count;
            SQLLEN countInd;
            retCode = SQLBindCol(hStmt, 1, SQL_C_USHORT, &count, 0, &countInd);
            if( !SQL_SUCCEEDED(retCode) )
                throw SQLException(SQL_HANDLE_STMT,hStmt);

            retCode = SQLFetch(hStmt);
            if( !SQL_SUCCEEDED(retCode) )
                throw SQLException(SQL_HANDLE_STMT,hStmt);

            outTableName->assign(predName+to_string(count));

            // Create the table.
            string sqlCreateTable = "CREATE TABLE "+(*outTableName)+" (";
            for( unsigned i=0; i<arity; i++ )
            {
                sqlCreateTable.append("attribute"+to_string(i)+" varchar(255)");
                if( i < arity-1 )
                    sqlCreateTable.append(", ");
            }
            sqlCreateTable.append(");");
            // Close the cursor.
            SQLCloseCursor(hStmt);
            retCode = SQLExecDirect(hStmt,(SQLCHAR*)sqlCreateTable.c_str(),SQL_NTS);
            if( !SQL_SUCCEEDED(retCode) )
                throw SQLException(SQL_HANDLE_STMT,hStmt);

            // Update table "tableNames".
            // FIXME: type value is still empty.
            string sqlUpdateTableNames = "INSERT INTO "+tableNames+
                    " VALUES ('"+(*outTableName)+"','"+predName+"',"+to_string(arity)+","+"'string');";
            // Close the cursor.
            SQLCloseCursor(hStmt);
            retCode = SQLExecDirect(hStmt,(SQLCHAR*)sqlUpdateTableNames.c_str(),SQL_NTS);
            if( !SQL_SUCCEEDED(retCode) )
                throw SQLException(SQL_HANDLE_STMT,hStmt);

            commit();
        }
        else
            throw SQLException(SQL_HANDLE_STMT,hStmt);

        retCode = SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hStmt);
    }
    catch( SQLException& exception )
    {
        delete outTableName;
        SQLSMALLINT i = 1;
        SQLSMALLINT MsgLen;
        SQLINTEGER NativeError;
        SQLCHAR SqlState[6];
        SQLCHAR Msg[SQL_MAX_MESSAGE_LENGTH];
        retCode = SQLGetDiagRec(exception.first, exception.second, i, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen);
        if( retCode == SQL_SUCCESS )
            ErrorMessage::errorDBConnection(Msg);
        else
            ErrorMessage::errorDBConnection("Unknown error");
    }
    return outTableName;
}

vector<string>*
DBConnection::retrieveTableSchema(
    const std::string& tableName,
    unsigned nAttributes ) const
{
    assert_msg( connected, "You have to first connect to a datasource." );
    vector<string>* attributesList = new vector<string>();
    SQLRETURN retCode;
    SQLHSTMT hStmt = 0;
    try
    {
        // Allocate statement handle
        retCode = SQLAllocHandle(SQL_HANDLE_STMT, hDBc, &hStmt);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hStmt);

        retCode = SQLColumns(hStmt, NULL, 0, NULL, 0, (SQLCHAR*)tableName.c_str(), SQL_NTS, NULL, 0);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hStmt);

        // Declare buffers for result set data
        unsigned STR_LEN = 128 + 1;
        char szColumnName[STR_LEN];
        //SQLCHAR szTypeName[STR_LEN];
        // Declare buffers for bytes available to return
        SQLLEN cbColumnName;
        //SQLINTEGER cbTypeName;
        // Bind columns in result set to buffers
        retCode = SQLBindCol(hStmt, 4, SQL_C_CHAR, szColumnName, STR_LEN, &cbColumnName);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hStmt);

        if( retCode == SQL_NO_DATA )
            throw tableName+": wrong table name! Retrieving its schema is not possible.";

        //SQLBindCol(hstmt, 6, SQL_C_CHAR, szTypeName, STR_LEN, &cbTypeName);
        while( SQL_SUCCEEDED(retCode = SQLFetch(hStmt)) )
        {
            attributesList->push_back(string(szColumnName));
        }

        // If attributeList were empty, table "tableName" would not exist.
        // That should not be possible because retrieveTableName is called
        // before, and that function creates the table if it doesn't exist.
        // Anyway, someone might call this function with a not valid table name.
        if( nAttributes != attributesList->size() )
            throw tableName+": wrong table name! Its schema does not match the arity.";

        retCode = SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hStmt);
    }
    catch( SQLException& exception )
    {
        delete attributesList;
        SQLSMALLINT i = 1;
        SQLSMALLINT MsgLen;
        SQLINTEGER NativeError;
        SQLCHAR SqlState[6];
        SQLCHAR Msg[SQL_MAX_MESSAGE_LENGTH];
        retCode = SQLGetDiagRec(exception.first, exception.second, i, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen);
        if( retCode == SQL_SUCCESS )
            ErrorMessage::errorDBConnection(Msg);
        else
            ErrorMessage::errorDBConnection("Unknown error");
    }
    catch( const string& genericException )
    {
        ErrorMessage::errorDBConnection(genericException);
    }
    return attributesList;
}

Timestamp
DBConnection::retrieveNextExecutionTimestamp()
{
    // If it has not been retrieved yet, do it.
    if( currentExecutionTimestamp == 0 )
    {
        assert_msg( connected, "You have to first connect to a datasource." );
        SQLRETURN retCode;
        SQLHSTMT hStmt = 0;
        try
        {
            // Allocate statement handle
            retCode = SQLAllocHandle(SQL_HANDLE_STMT, hDBc, &hStmt);
            if( !SQL_SUCCEEDED(retCode) )
                throw SQLException(SQL_HANDLE_STMT,hStmt);

            // FIXME: sql code should not be included in this class.
            string executionTimestamp(EXECUTION_TIMESTAMP);
            string sqlId = "SELECT id FROM "+executionTimestamp;
            retCode = SQLExecDirect(hStmt,(SQLCHAR*)sqlId.c_str(),SQL_NTS);

            if( !SQL_SUCCEEDED(retCode) )
                throw SQLException(SQL_HANDLE_STMT,hStmt);

            // Bind columns in result set to buffers
            retCode = SQLBindCol(hStmt, 1, SQL_C_UBIGINT, &currentExecutionTimestamp, 0, NULL);
            if( !SQL_SUCCEEDED(retCode) )
                throw SQLException(SQL_HANDLE_STMT,hStmt);

            // There should be exactly one record.
            // If no matchings are found, create one.
            retCode = SQLFetch(hStmt);
            if( SQL_SUCCEEDED(retCode) )
            {
                // Since the retrieved timestamp will be used for the current
                // execution, the next available timestamp should be updated.
                string sqlUpdate = "UPDATE "+executionTimestamp+
                        " SET id = "+to_string(currentExecutionTimestamp+1)+";";
                // Close the cursor.
                SQLCloseCursor(hStmt);
                retCode = SQLExecDirect(hStmt,(SQLCHAR*)sqlUpdate.c_str(),SQL_NTS);
                if( !SQL_SUCCEEDED(retCode) )
                    throw SQLException(SQL_HANDLE_STMT,hStmt);
            }
            else if( retCode == SQL_NO_DATA )
            {
                // If such a value does not exist, insert a new record.
                setAutoCommit(false);
                // Execution IDs start from 1, hence the next available is 2.
                currentExecutionTimestamp = 1;
                string sqlUpdateTableExecution = "INSERT INTO "+executionTimestamp+
                        " VALUES ("+to_string(currentExecutionTimestamp+1)+");";
                // Close the cursor.
                SQLCloseCursor(hStmt);
                retCode = SQLExecDirect(hStmt,(SQLCHAR*)sqlUpdateTableExecution.c_str(),SQL_NTS);
                if( !SQL_SUCCEEDED(retCode) )
                    throw SQLException(SQL_HANDLE_STMT,hStmt);

                commit();
            }
            else
                throw SQLException(SQL_HANDLE_STMT,hStmt);
        }
        catch( SQLException& exception )
        {
            SQLSMALLINT i = 1;
            SQLSMALLINT MsgLen;
            SQLINTEGER NativeError;
            SQLCHAR SqlState[6];
            SQLCHAR Msg[SQL_MAX_MESSAGE_LENGTH];
            retCode = SQLGetDiagRec(exception.first, exception.second, i, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen);
            if( retCode == SQL_SUCCESS )
                ErrorMessage::errorDBConnection(Msg);
            else
                ErrorMessage::errorDBConnection("Unknown error");
        }
    }
    return currentExecutionTimestamp;
}

Timestamp
DBConnection::retrieveNextTableTimestamp(
    const std::string& tableName ) const
{
    assert_msg( connected, "You have to first connect to a datasource." );
    Timestamp nextId = 1;
    SQLRETURN retCode;
    SQLHSTMT hStmt = 0;
    try
    {
        // Allocate statement handle
        retCode = SQLAllocHandle(SQL_HANDLE_STMT, hDBc, &hStmt);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hStmt);

        // FIXME: sql code should not be included in this class.
        string predicateTimestamp(PREDICATE_TIMESTAMP);
        string sqlId = "SELECT next_id FROM "+predicateTimestamp+" WHERE table_name = '"+tableName+"';";
        retCode = SQLExecDirect(hStmt,(SQLCHAR*)sqlId.c_str(),SQL_NTS);

        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hStmt);

        // Bind columns in result set to buffers
        retCode = SQLBindCol(hStmt, 1, SQL_C_UBIGINT, &nextId, 0, NULL);
        if( !SQL_SUCCEEDED(retCode) )
            throw SQLException(SQL_HANDLE_STMT,hStmt);

        // There should be exactly one record.
        // If no matchings are found, create one.
        retCode = SQLFetch(hStmt);
        if( SQL_SUCCEEDED(retCode) )
        {
            // Since the retrieved timestamp will be used for the current
            // execution, the next available timestamp should be updated.
            string sqlUpdate = "UPDATE "+predicateTimestamp+
                    " SET next_id = "+to_string(nextId+1)+
                    " WHERE next_id = "+to_string(nextId)+" and table_name = '"+tableName+"';";
            // Close the cursor.
            SQLCloseCursor(hStmt);
            retCode = SQLExecDirect(hStmt,(SQLCHAR*)sqlUpdate.c_str(),SQL_NTS);
            if( !SQL_SUCCEEDED(retCode) )
                throw SQLException(SQL_HANDLE_STMT,hStmt);
        }
        else if( retCode == SQL_NO_DATA )
        {
            // If such a value does not exist, insert a new record.
            setAutoCommit(false);
            // Available IDs start from 1, hence the next one is 2.
            string sqlUpdateTableExecution = "INSERT INTO "+predicateTimestamp+
                    " VALUES ('"+tableName+"',"+to_string(nextId+1)+");";
            // Close the cursor.
            SQLCloseCursor(hStmt);
            retCode = SQLExecDirect(hStmt,(SQLCHAR*)sqlUpdateTableExecution.c_str(),SQL_NTS);
            if( !SQL_SUCCEEDED(retCode) )
                throw SQLException(SQL_HANDLE_STMT,hStmt);

            commit();
        }
        else
            throw SQLException(SQL_HANDLE_STMT,hStmt);
    }
    catch( SQLException& exception )
    {
        SQLSMALLINT i = 1;
        SQLSMALLINT MsgLen;
        SQLINTEGER NativeError;
        SQLCHAR SqlState[6];
        SQLCHAR Msg[SQL_MAX_MESSAGE_LENGTH];
        retCode = SQLGetDiagRec(exception.first, exception.second, i, SqlState, &NativeError,Msg, sizeof(Msg), &MsgLen);
        if( retCode == SQL_SUCCESS )
            ErrorMessage::errorDBConnection(Msg);
        else
            ErrorMessage::errorDBConnection("Unknown error");
    }
    return nextId;
}
