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

#include "QueryObject.h"
#include "../../util/Assert.h"

using namespace std;
using namespace DLV2::DB;

QueryObject::QueryObject():
        sqlBuilder(NULL)
{
}

QueryObject::QueryObject(
    const QueryObject& obj ):
        targetPredicate(obj.targetPredicate),
        attributesToSelect(obj.attributesToSelect),
        sourcePredicates(obj.sourcePredicates),
        conditions(obj.conditions)
{
    if( obj.sqlBuilder == &obj )
        sqlBuilder = this;
    else
        sqlBuilder = obj.sqlBuilder;
}

void
QueryObject::setSQLBuilder(
    SQLBuilder* build )
{
    assert_msg( build != NULL, "Trying to set a null sql builder." );
    sqlBuilder = build;
}

string*
QueryObject::getSQL()
{
    assert_msg( sqlBuilder != NULL, "Trying to get the SQL version of a query object with a null query builder." );
    return sqlBuilder->generateSQL(this);
}

string*
QueryObject::generateSQL(
    QueryObject* qObj )
{
    assert_msg( qObj != NULL, "Null query object" );
    assert_msg( qObj->getTargetPredicate().length() > 0, "Null target predicate" );
    assert_msg( qObj->getAttributesToSelect().size() > 0, "No attributes to select" );
    assert_msg( qObj->getSourcePredicates().size() > 0, "Null source predicate" );
    string* sql = new string();
    sql->append("INSERT INTO ").append(qObj->getTargetPredicate()).append(" ( SELECT ");
    for( unsigned i=0; i<qObj->getAttributesToSelect().size(); i++ )
    {
        sql->append(qObj->getAttributesToSelect().at(i));
        if( i < qObj->getAttributesToSelect().size()-1 )
            sql->append(",");
    }
    sql->append(" FROM ");
    for( unsigned i=0; i<qObj->getSourcePredicates().size(); i++ )
    {
        sql->append(qObj->getSourcePredicates().at(i));
        if( i < qObj->getSourcePredicates().size()-1 )
            sql->append(",");
    }
    if( qObj->getConditions().size() > 0 )
    {
        sql->append(" WHERE ");
        for( unsigned i=0; i<qObj->getConditions().size(); i++ )
        {
            sql->append(qObj->getConditions().at(i).first)
                    .append("=")
                    .append(qObj->getConditions().at(i).second);
            if( i < qObj->getConditions().size()-1 )
                sql->append(" AND ");
        }
    }
    sql->append(" EXCEPT (SELECT * FROM ")
            .append(qObj->getTargetPredicate())
            .append("))");
    return sql;
}