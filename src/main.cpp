#include <iostream>
#include "DLV2Facade.h"
#include "util/Options.h"

#include "depgraph/LabeledDependencyGraph.h"
#include "depgraph/DepGraphOnlyPositiveEdgesStrategy.h"
#include "grounder/hash/Hashable.h"

using namespace std;

/*
 *  Link youtrack: http://dlv2.myjetbrains.com/youtrack/dashboard
 */

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
