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

#include "DLVDBFacade.h"
#include "queries/QueryObject.h"
#include "../util/Assert.h"
#include "../util/ErrorMessage.h"
#include <string>

using namespace std;
using namespace DLV2::DB;

DLVDBFacade::DLVDBFacade(
    DBProgram& p,
    DBConnection& con):
        program(p),
        connection(con)
{
}


void
DLVDBFacade::solve()
{
    connection.setAutoCommit(false);
    // First of all, consider the query plan given
    // by the topologically ordered sequence of the strictly
    // connected components of the dependency graph.
    program.computeStrictlyConnectedComponents();
    if( program.isCyclic() )
        ErrorMessage::errorGeneric("Only acyclic program are allowed at the moment");
    if( !program.isStratified() )
        ErrorMessage::errorGeneric("Only stratified program are allowed at the moment");
    if( program.isDisjunctive() )
        ErrorMessage::errorGeneric("Only disjunction-free programs are allowed at the moment");
    // Boost function "strong_components" computes the 
    // SCCs of a graph and returns them in a reverse 
    // topological order.    
    program.computeComponentSubPrograms();
    const vector< DBSubProgram< index_t > >& subPrograms = program.getComponentSubPrograms();
    // Distinguishing recursive rules from non-recursive ones is now possible.
    // Thus, query objects can be computed only here.
    program.computeQueryObjects();
    const vector< QueryObject* >& factQueries = program.getFactQueryObjects();
    const vector< QueryObject* >& ruleQueries = program.getRuleQueryObjects();
            
    // First of all, execute queries related to the facts in input. 
    for( index_t i=0; i<factQueries.size(); i++ )
    {
        QueryObject* queryObject = factQueries.at(i);
        assert_msg( queryObject != NULL, "Null query object" );
        // FIXME: That builder can handle only Postgres databases.
        queryObject->setSQLBuilder(queryObject);
        string* sql = queryObject->getSQL(); 
        cout << *sql << endl;
        connection.executeSQLStatement(*sql);
        delete sql;
    }

    // Execute the subprogram related to each member of the current component.
    for( long int i=subPrograms.size()-1; i>=0; i-- )
    {
        for( DBSubProgram< index_t >::const_iterator it = subPrograms[i].exitBegin();
                it != subPrograms[i].exitEnd();
                it++ )
        {
            assert_msg( (0 <= *it && *it < ruleQueries.size()), "Index out of range" );
            QueryObject* queryObject = ruleQueries.at(*it);
            assert_msg( queryObject != NULL, "Null query object" );
            // FIXME: That builder can handle only Postgres databases.
            queryObject->setSQLBuilder(queryObject);
            string* sql = queryObject->getSQL(); 
            cout << *sql << endl;
            connection.executeSQLStatement(*sql);
            delete sql;
        }
        for( DBSubProgram< index_t >::const_iterator it = subPrograms[i].recBegin();
                it != subPrograms[i].recEnd();
                it++ )
        {
            // TODO ...
        }
    }
    connection.commit();
}
