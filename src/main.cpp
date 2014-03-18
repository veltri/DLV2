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
    Term* v = new Variable(0);
    Term* s = new StringConstant("x1");
    Term* i = new IntegerConstant(10);
    vector<Term*> terms;
    terms.push_back(v);
    terms.push_back(s);
    terms.push_back(i);
    Atom a("s",3,terms);
    Atom b("p",3,terms);
    Atom c("r",3,terms);
    Rule r;
    Literal l1(a,false);
    Literal l2(a,true);
    Literal l3(c,false);
    r.addToBody(l1);
    r.addToBody(l2);
    r.addToBody(l3);
    r.addToHead(b);
    cout << "Rule: " << r << endl;
    delete i;
    delete s;
    delete v;
    
    InputBuilder* builder = new SimpleInputBuilder();
    InputDirector::getInstance().configureBuilder(builder);
    InputDirector::getInstance().parse(argc,argv);
    
    cout << InputDirector::getInstance().getProgram();
    
    InputDirector::free();
    delete builder;
        
    return 0;
}