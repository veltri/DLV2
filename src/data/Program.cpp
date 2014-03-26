#include "Program.h"

Program::Program( 
    const Program& p ): 
        rules(p.rules), 
        constraints(p.constraints),
        weakConstraints(p.weakConstraints) 
{
    
}

void 
Program::addRule( 
    const Rule& r ) 
{ 
    rules.push_back(r); 
}

void 
Program::addConstraint( 
    const Constraint& c ) 
{ 
    constraints.push_back(c); 
}

void 
Program::addWeakConstraint( 
    const WeakConstraint& wc ) 
{ 
    weakConstraints.push_back(wc); 
}
