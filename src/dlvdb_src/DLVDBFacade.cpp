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
#include <string>

using namespace std;
using namespace DLV2::DB;

DLVDBFacade::DLVDBFacade(
    DBProgram& p,
    LabeledDependencyGraph<>& dG, 
    DBConnection& con):
        program(p),
        depGraph(dG),
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
    depGraph.computeStronglyConnectedComponents();
    // At the moment, only acyclic programs can be handled.
    assert_msg( !depGraph.isCyclic(), "Only acyclic program are allowed" );
    assert_msg( depGraph.isStratified(), "Only stratified program are allowed" );
    // Boost function "strong_components" computes the 
    // SCCs of a graph and returns them in a reverse 
    // topological order.
    const Components& components = depGraph.getComponentList();
    assert_msg( components.size() > 0, "The dependency graph has no SCCs" );
    for( unsigned i=components.size()-1; i>=0; i-- )
    {
        // Execute the subprogram related to 
        // each member of the current component.
        for( unsigned j=0; j<components[i].size(); j++ )
        {
            const string& predName = depGraph.getLabelOfVertex(components[i][j]);
            set<unsigned>* subProgram = program.getSubProgram(predName);
            for( set<unsigned>::const_iterator it = subProgram->begin();
                    it != subProgram->end();
                    it++ )
            {
                QueryObject* queryObject = program.getQueryObject(*it);
                assert_msg( queryObject != NULL, "Null query object" );
                // FIXME: That builder can handle only Postgres databases.
                queryObject->setSQLBuilder(queryObject);
                string* sql = queryObject->getSQL(); 
                cout << i << ":    " << *sql << endl;
                connection.executeSQLStatement(*sql);
                delete sql;
            }
        }
    }
    connection.commit();
}
