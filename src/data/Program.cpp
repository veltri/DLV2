#include "Program.h"

Program::Program( 
    const Program& p ): 
        rules(p.rules), 
        constraints(p.constraints),
        weakConstraints(p.weakConstraints),
        choiceRules(p.choiceRules)
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

void 
Program::addChoiceRule( 
    const ChoiceRule& cr ) 
{ 
    choiceRules.push_back(cr); 
}
