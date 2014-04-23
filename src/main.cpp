#include <iostream>
#include <fstream>
#include "DLV2Facade.h"
#include "util/Options.h"

using namespace std;

int main(int argc, char** argv)
{  
    DLV2::DLV2Facade dlv2Facade;

    dlv2Facade.parseOptions(argc,argv);
    dlv2Facade.greetings();
    int parserExit = dlv2Facade.readInput();
    //cout << parserExit << endl;
    if(parserExit == 0)
    {
    	dlv2Facade.solve();
    }
        
    return parserExit;
}
