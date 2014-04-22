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

#include "WeakConstraint.h"

WeakConstraint::WeakConstraint( 
    vector<Literal> b,
    Term* w,
    Term* l,
    vector<Term> t ):
        body(b),
        terms(t)
{
    if( w != NULL )
        weight = new Term(*w);
    else
        weight = NULL;
    if( l != NULL )
        level = new Term(*l);
    else
        level = NULL;
}

WeakConstraint::WeakConstraint(
    const WeakConstraint& wc):
        body(wc.body),
        terms(wc.terms)
{
    if( wc.weight != NULL )
        weight = new Term(*wc.weight);
    else
        weight = NULL;
    if( wc.level != NULL )
        level = new Term(*wc.level);
    else
        level = NULL;
}

WeakConstraint::~WeakConstraint()
{
    if( level != NULL )
        delete level;
    if( weight != NULL )
        delete weight;
}