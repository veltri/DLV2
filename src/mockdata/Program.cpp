/*
 *
 *  Copyright 2014 Mario Alviano, Carmine Dodaro, Francesco Ricca and
 *                 Pierfrancesco Veltri.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#include "Program.h"

namespace DLV2
{

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

};