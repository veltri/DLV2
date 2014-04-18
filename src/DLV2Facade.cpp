#include "DLV2Facade.h"
#include "util/Assert.h"
#include "util/ErrorMessage.h"
#include "util/Options.h"
#include "input/InputDirector.h"
#include "input/SimpleInputBuilder.h"
#include "input/SelectorBuilder.h"

void
DLV2Facade::greetings()
{
    // FIXME
    if( !getOptions().getOutputPolicy() == OUTPUT_SILENT )
        cout << DLV2_STRING << endl;
}

void 
DLV2Facade::readInput()
{
	switch( getOptions().inputBuilderPolicy() )
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

    assert_msg( InputDirector::getInstance().getBuilder() == NULL,
            "Null input-builder, cannot start the parsing process.");

	InputDirector::getInstance().configureBuilder(builder);
    InputDirector::getInstance().parse(getOptions().getInputFiles());
}

void
DLV2Facade::solve()
{
	// FIXME: this switch should be done differently else.

	switch( getOptions().inputBuilderPolicy() )
	{

	case BUILDER_SELECTOR:
	{
		SelectorBuilder* selectorBuilder = static_cast<SelectorBuilder*>(builder);

		int ecode = selectorBuilder->getSolverToCall();
        delete selectorBuilder;
        free();

        exit(ecode);

	}
        break;

	case BUILDER_MOCK_OBJECTS:
	{
		SimpleInputBuilder* simpleBuilder = static_cast<SimpleInputBuilder*>(builder);
        cout << simpleBuilder->getProgram();
        if( simpleBuilder->getQuery() )
            cout << *(simpleBuilder->getQuery()) << "?" << endl;
        delete simpleBuilder;
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

void
DLV2Facade::free()
{
   InputDirector::free();
}

DLV2Facade::~DLV2Facade()
{
    if(builder != NULL) delete builder;
}
