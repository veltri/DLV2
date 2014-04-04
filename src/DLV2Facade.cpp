#include "DLV2Facade.h"
#include "util/Assert.h"
#include "util/ErrorMessage.h"
#include "input/InputDirector.h"
#include "input/SimpleInputBuilder.h"

void 
DLV2Facade::readInput()
{
    InputDirector::getInstance().parse(inputFiles);
}

void 
DLV2Facade::setInputHandlingPolicy( 
    INPUT_HANDLING_POLICY inputPolicy )
{
    switch( inputPolicy )
    {
        case INPUT_TESTING_OBJECTS:
            builder = new SimpleInputBuilder();
            InputDirector::getInstance().configureBuilder(builder);
            break;
        case INPUT_DLV_DB:
            // TODO
            break;
        case INPUT_IN_MEMORY:
            // TODO
            ErrorMessage::errorGeneric( "In-memory version not implemented yet! Bye." );
            break;
    }
}

void
DLV2Facade::solve()
{
    if( printProgram )
    {
        SimpleInputBuilder* simpleBuilder = (SimpleInputBuilder*)builder;
        cout << simpleBuilder->getProgram();
        if( simpleBuilder->getQuery() )
            cout << *(simpleBuilder->getQuery()) << "?" << endl;
    }
    else
        // TODO 
        ErrorMessage::errorGeneric( "No solver available! Bye" );
}

void
DLV2Facade::free()
{
    InputDirector::free();
    if( builder )
        delete builder;
}
