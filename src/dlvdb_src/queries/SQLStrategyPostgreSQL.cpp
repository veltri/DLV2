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
 * File:   SQLStrategyPostgreSQL.cpp
 * Author: pierfrancesco
 *
 * Created on 22 ottobre 2014, 16.34
 */

#include "SQLStrategyPostgreSQL.h"

using namespace std;
using namespace DLV2::DB;

void
SQLStrategyPostgreSQL::getRuleInSQL(
    string& sqlOutput ) const
{
    assert_msg( targetTable.length() > 0, "Null target predicate" );
    assert_msg( attributesToSelect.size() > 0, "No attributes to select" );
    assert_msg( sourceTables.size() > 0, "Null source predicate" );
    assert_msg( sqlOutput.size() == 0, "The output string should be empty" );
    sqlOutput.append("INSERT INTO ").append(targetTable).append(" ( SELECT ");
    for( unsigned i=0; i<attributesToSelect.size(); i++ )
    {
        sqlOutput.append(attributesToSelect.at(i));
        if( i < attributesToSelect.size()-1 )
            sqlOutput.append(",");
    }
    sqlOutput.append(" FROM ");
    for( unsigned i=0; i<sourceTables.size(); i++ )
    {
        sqlOutput.append(sourceTables.at(i));
        if( i < sourceTables.size()-1 )
            sqlOutput.append(",");
    }
    if( conditions.size() > 0 )
    {
        sqlOutput.append(" WHERE ");
        for( unsigned i=0; i<conditions.size(); i++ )
        {
            sqlOutput.append(conditions.at(i).first)
                                .append("=")
                                .append(conditions.at(i).second);
            if( i < conditions.size()-1 )
                sqlOutput.append(" AND ");
        }
    }
    sqlOutput.append(" EXCEPT (SELECT * FROM ")
                        .append(targetTable)
                        .append("))");
}

void
SQLStrategyPostgreSQL::getFactInSQL(
    string& sqlOutput ) const
{
    // TODO
}
