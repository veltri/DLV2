#include <iostream>
#include <cstring>
#include "data/Program.h"
#include "data/IntegerConstant.h"
#include "data/StringConstant.h"
#include "data/Variable.h"
#include "input/InputDirector.h"
#include "input/SimpleInputBuilder.h"

using namespace std;

int main(int argc, char** argv)
{  
    InputBuilder* builder = new SimpleInputBuilder();
    InputDirector::getInstance().configureBuilder(builder);
    InputDirector::getInstance().parse(argc,argv);
    
    cout << InputDirector::getInstance().getProgram();
    
    InputDirector::free();
    delete builder;
        
    return 0;
}