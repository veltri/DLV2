#include "DLV2Facade.h"
#include "util/Assert.h"
#include "util/ErrorMessage.h"
#include "input/InputDirector.h"
#include "input/SimpleInputBuilder.h"

void
DLV2Facade::greetings()
{
    // FIXME
    if( !outputSilent )
        cout << DLV2_STRING << endl;
}


void 
DLV2Facade::readInput()
{
    assert_msg( InputDirector::getInstance().getBuilder() != NULL, 
            "Null input-builder, cannot start the parsing process.");
    InputDirector::getInstance().parse(inputFiles);
}

void
DLV2Facade::solve()
{
    // FIXME
    if( printProgram )
    {
        assert_msg( InputDirector::getInstance().getBuilder() != NULL, 
                "Null input-builder, cannot start the solving process." );
        SimpleInputBuilder* simpleBuilder = 
                (SimpleInputBuilder*)InputDirector::getInstance().getBuilder();
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
    if( InputDirector::getInstance().getBuilder() )
        delete InputDirector::getInstance().getBuilder();
    InputDirector::free();
}

void 
DLV2Facade::setInputHandlingPolicy( 
    INPUT_HANDLING_POLICY inputPolicy )
{
    switch( inputPolicy )
    {
        case INPUT_MOCK_OBJECTS:
            InputDirector::getInstance().configureBuilder(new SimpleInputBuilder());
            break;
        case INPUT_DLV_DB:
            // TODO
            ErrorMessage::errorGeneric( "--dlv-db: Not supported yet! Bye." );
            break;
        case INPUT_IN_MEMORY:
            // TODO
            ErrorMessage::errorGeneric( "--inmemory: Not supported yet! Bye." );
            break;
    }
}

void 
DLV2Facade::setOutputPolicy( 
    OUTPUT_POLICY outputPolicy )
{ 
    // FIXME
    switch( outputPolicy )
    {
        case OUTPUT_SILENT:
            outputSilent = true;
            break;
    }
}
