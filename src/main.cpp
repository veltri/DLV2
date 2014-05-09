#include <iostream>
#include <fstream>
#include "DLV2Facade.h"
#include "util/Options.h"

#include "depgraph/DependencyGraph.h"
#include "depgraph/DepGraphOnlyPositiveEdgesStrategy.h"
#include <string>

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
    DLV2::DependencyGraph<DLV2::DepGraphOnlyPositiveEdgesStrategy> g;
    g.addEdge(1,2);
    
/*        
    DLV2::LabeledDependencyGraph depGraph;
    depGraph.addPositiveEdge("ciao","hello");
    depGraph.addPositiveEdge("hello","ciao");
    depGraph.computeStronglyConnectedComponents();
*/    
    return parserExit;
}
