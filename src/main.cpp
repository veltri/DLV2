#include <iostream>
#include "DLV2Facade.h"
#include "util/Options.h"

using namespace std;

int main(int argc, char** argv)
{  
    dlv2::Options::globalOptions()->init( argc, argv );

    DLV2Facade dlv2Facade;

    dlv2Facade.greetings();
    dlv2Facade.readInput();
    dlv2Facade.solve();
    // FIXME
    dlv2Facade.free();
    /*InputBuilder* builder = new SimpleInputBuilder();
    InputDirector::getInstance().configureBuilder(builder);
    InputDirector::getInstance().parse(argc,argv);
    
    SimpleInputBuilder* simpleBuilder = (SimpleInputBuilder*)builder;
    cout << simpleBuilder->getProgram();
    if( simpleBuilder->getQuery() )
        cout << *(simpleBuilder->getQuery()) << "?" << endl;
    
    InputDirector::free();
    delete builder;*/
        
    return 0;
}
