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
#include "input/SimpleInputBuilder.h"
#include "input/SelectorBuilder.h"
#include "input/Buffer.h"

//extern Buffer theBuffer;

#include <fstream>
#include <sstream>
using namespace std;

namespace DLV2
{

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
    switch( getOptions().getInputBuilderPolicy() )
    {
        case BUILDER_SELECTOR:
            builder = new SelectorBuilder();
            break;

        case BUILDER_MOCK_OBJECTS:
            builder = new SimpleInputBuilder();
            break;

        case BUILDER_DLV_DB:
            // TODO
            ErrorMessage::errorGeneric( "--dlv-db: Not supported yet! Bye." );
            break;

        case BUILDER_IN_MEMORY:
            // TODO
            ErrorMessage::errorGeneric( "--inmemory: Not supported yet! Bye." );
            break;

        default:
            ErrorMessage::errorGeneric( "WARNING: No such builder available!" );
    }

    assert_msg( director.getBuilder() == NULL,
            "Null input-builder, cannot start the parsing process.");

    director.configureBuilder(builder);
    return director.parse(getOptions().getInputFiles());
}

void
DLV2Facade::solve()
{
	// FIXME: this switch should be done differently else.

	switch( getOptions().getInputBuilderPolicy() )
	{

	case BUILDER_SELECTOR:
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
                else{
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
        break;

        case BUILDER_MOCK_OBJECTS:
        {
            SimpleInputBuilder* simpleBuilder = static_cast<SimpleInputBuilder*>(builder);
            cout << simpleBuilder->getProgram();
            if( simpleBuilder->getQuery() )
                cout << *(simpleBuilder->getQuery()) << "?" << endl;
        }
        break;

        case BUILDER_DLV_DB:
            // TODO
            ErrorMessage::errorGeneric( "No solver available! Bye" );
            break;

        case BUILDER_IN_MEMORY:
            // TODO
            ErrorMessage::errorGeneric( "No solver available! Bye" );
            break;

        default:
            ErrorMessage::errorGeneric( "No solver available! Bye" );
        }
    
}

DLV2Facade::~DLV2Facade()
{
    getOptions().finalizeGlobalOptions();
    if( builder != NULL ) 
        delete builder;
}

};