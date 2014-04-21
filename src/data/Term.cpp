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

#include "Term.h"

Term::Term( 
    unsigned i ):
        index(Names::addIntegerConstant(i)),
        varName(""),
        type(Integer)
{
    
}

Term::Term( 
    string v ):
        index(Names::addStringConstant(v)),
        varName(""),
        type(String)
{
    
}

Term::Term(
    unsigned i, 
    string v ):
        index(i),
        varName(v),
        type(Variable)
{
    
}
    
Term::Term( 
    const Term& t ):
        index(t.index),
        varName(t.varName),
        type(t.type)
{
    
}
