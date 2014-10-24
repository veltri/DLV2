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

#include "DLV2Facade.h"
#include "util/Assert.h"
#include "util/ErrorMessage.h"
#include "util/DBConnection.h"
#include "input/SimpleInputBuilder.h"
#include "input/SelectorBuilder.h"
#include "input/Buffer.h"
#include "input/DepGraphBuilder.h"
#include "input/EmptyInputBuilder.h"
#include "dlvdb_src/input/DBInputBuilder.h"
#include "dlvdb_src/DLVDBFacade.h"

//extern Buffer theBuffer;

#include <cstdio>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;
using namespace DLV2;
using namespace DLV2::DB;

void 
DLV2Facade::parseOptions(
    int argc, 
    char* const* argv )
{
    getOptions().init(argc,argv);
}

void
DLV2Facade::greetings()
{
    // FIXME
    if( !getOptions().getOutputPolicy() == OUTPUT_SILENT )
        cout << DLV2_STRING << endl;
}

int
DLV2Facade::readInput()
{
    if( getOptions().isAspCore2Strict() )
        director.setParserConstraint(new ParserConstraintAspCore2Strict());
        
    switch( getOptions().getInputBuilderPolicy() )
    {
        case BUILDER_MOCK_OBJECTS:
            builder = new SimpleInputBuilder();
            break;

        case BUILDER_SELECTOR:
            builder = new SelectorBuilder();
            break;
            
        case BUILDER_DEPGRAPH:
            builder = new DepGraphBuilder();
            break;
            
        case BUILDER_DLV_DB:
            DBConnection::globalDBConnection()->connect(
                    getOptions().getDBDataSource(),
                    getOptions().getDBUsername(),
                    getOptions().getDBPassword());
            builder = new DBInputBuilder(*DBConnection::globalDBConnection());
            break;

        case BUILDER_IN_MEMORY:
            // TODO
            ErrorMessage::errorGeneric( "--inmemory: Not supported yet! Bye." );
            break;
            
        case BUILDER_EMPTY:
            builder = new EmptyInputBuilder();
            break;

        default:
            ErrorMessage::errorGeneric( "WARNING: No such builder available!" );
    }

    assert_msg( director.getBuilder() == NULL,
            "Null input-builder, cannot start the parsing process.");
    director.configureBuilder(builder);
           
    clock_t start = clock();
    int error = director.parse(getOptions().getInputFiles());
    parserDuration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    
    return error;
}

void
DLV2Facade::solve()
{
    if( getOptions().getPrintProgram() )
    {
        if( getOptions().getInputBuilderPolicy() == BUILDER_SELECTOR )
        {
            SelectorBuilder* selectorBuilder = static_cast<SelectorBuilder*>(builder);

            ostringstream s1;
            s1 << "mkfifo /tmp/wasppipe_" << getOptions().getNamedpipe();
            system(s1.str().c_str());

            int ecode = selectorBuilder->getSolverToCall();

            if(ecode == 0)
            {
                //cerr << "WASP" << endl;
                cout<<"0"<<endl;
            }
            else
            {
                //cerr << "DLV" << endl;
                cout<<"1"<<endl;
                //system("cat - < /tmp/wasppipe");
            }
            cout.flush();

            ostringstream s;
            s << "/tmp/wasppipe_" << getOptions().getNamedpipe();
            fstream o(s.str(), std::ios::out);
            //cerr << "scrivo" << endl;
            //theBuffer.flushOn(o);
            o.flush();
            //cerr << "finito" << endl;
            o.close();

            //delete selectorBuilder;
            //free();

            //exit(ecode);
        }
        else if( getOptions().getInputBuilderPolicy() == BUILDER_MOCK_OBJECTS )
        {
            SimpleInputBuilder* simpleBuilder = static_cast<SimpleInputBuilder*>(builder);
            cout << simpleBuilder->getProgram();
            if( simpleBuilder->getQuery() )
                cout << *(simpleBuilder->getQuery()) << "?" << endl;
        }
        else
            ErrorMessage::errorGeneric( "Not valid solver to print the input program! Bye" );
    }
        
    if( getOptions().getPrintDepGraph() )
    {
        if( getOptions().getInputBuilderPolicy() == BUILDER_DEPGRAPH )
        {
            DepGraphBuilder* depGraphBuilder = static_cast<DepGraphBuilder*>(builder);
            // Compute strongly connected components.
            depGraphBuilder->getLabeledDependencyGraph().computeStronglyConnectedComponents();
            cout << depGraphBuilder->getLabeledDependencyGraph() << endl;
        }
        else
            ErrorMessage::errorGeneric( "Not valid solver to print the dependency graph! Bye" );
    }
    
    if( getOptions().getInputBuilderPolicy() == BUILDER_DLV_DB )
    {
        DBInputBuilder* dbInputBuilder = static_cast<DBInputBuilder*>(builder);
        DBProgram* program = dbInputBuilder->getProgram();
        assert_msg( program != NULL, "Null input program" );
        DBAtom* query = dbInputBuilder->getQuery();
        
        DLVDBFacade dlvdbFacade(
            *program,
            *DBConnection::globalDBConnection());
        
        dlvdbFacade.solve();

        if( query != NULL )
            delete query;
        if( program != NULL )
            delete program;
    }
    
    if( getOptions().getPrintStatistics() )
    {
        cerr << endl << "***FINAL STATISTICS***" << endl;
        cerr << "Parsing time: " << parserDuration << "s" << endl;
    }
    
}

DLV2Facade::~DLV2Facade()
{
    getOptions().finalizeGlobalOptions();
    if( builder != NULL ) 
        delete builder;
}
