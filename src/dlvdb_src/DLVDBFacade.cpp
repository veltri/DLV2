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
#include "queries/SQLStrategyPostgreSQL.h"
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

    // If the program is executable, start the transaction;
    connection.setAutoCommit(false);
    // Boost function "strong_components" computes the 
    // SCCs of a graph and returns them in a reverse 
    // topological order.    
    program.computeComponentSubPrograms();
    const vector< DBSubProgram >& subPrograms = program.getComponentSubPrograms();
    // Before starting the generation of the SQL queries, set the SQL generation strategy.
    program.setSQLStrategy(new SQLStrategyPostgreSQL(&program));
    // First of all, execute queries related to the facts in input. 
    for( typename vector< DBRule* >::const_iterator factIt = program.getFacts().begin();
            factIt != program.getFacts().end();
            factIt++ )
    {
        assert_msg( *factIt != NULL, "Null fact" );
        const string& sql = program.getFactQuery(*factIt);
        cout << sql << endl;
//        connection.executeSQLStatement(sql);
    }

    // Execute the subprogram related to each member of the current component.
    for( long int i=subPrograms.size()-1; i>=0; i-- )
    {
        for( DBSubProgram::const_iterator ruleIt = subPrograms[i].exitBegin();
                ruleIt != subPrograms[i].exitEnd();
                ruleIt++ )
        {
            assert_msg( *ruleIt != NULL, "Null rule" );
            // Distinguishing recursive rules from non-recursive ones is now possible.
            // Thus, query objects can be computed only here.
            const string& sql = program.getRuleQuery(*ruleIt);
            cout << sql << endl;
//            connection.executeSQLStatement(sql);
        }
        for( DBSubProgram::const_iterator ruleIt = subPrograms[i].recBegin();
                ruleIt != subPrograms[i].recEnd();
                ruleIt++ )
        {
            // TODO ...
        }
    }
    connection.commit();
}
