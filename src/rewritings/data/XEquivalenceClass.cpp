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

/* 
 * File:   XEquivalenceClass.cpp
 * Author: pierfrancesco
 *
 * Created on 09 gennaio 2015, 12.55
 */

#include "XEquivalenceClass.h"
#include "../../util/Assert.h"
#include <sstream>

using namespace std;
using namespace DLV2::REWRITERS;

XEquivalenceClass::XEquivalenceClass(
    XProgram& p ):
        program(p),
        representativeTerm(NULL),
        standardVars(),
        frontierVars(),
        existentialVars(),
        constants()
{
}

XEquivalenceClass::XEquivalenceClass(
    const XEquivalenceClass& ec ):
        program(ec.program),
        representativeTerm(NULL),
        standardVars(ec.standardVars),
        frontierVars(ec.frontierVars),
        existentialVars(ec.existentialVars),
        constants(ec.constants)
{
    if( ec.representativeTerm != NULL )
        representativeTerm = new XTerm(*ec.representativeTerm);
}

XEquivalenceClass::~XEquivalenceClass()
{
    if( representativeTerm != NULL )
        delete representativeTerm;
}

void
XEquivalenceClass::pushTerm(
    const XPartitionMapIterator& termIt,
    const XTermType& termType )
{
    // For each term at most one push is done.
    // Thus, a check about multiple additions of the same term would be useless.
    switch( termType )
    {
    case Variable:
        standardVars.push_back(termIt);
        break;
    case FrontierVariable:
        frontierVars.push_back(termIt);
        break;
    case ExistentialVariable:
        existentialVars.push_back(termIt);
        break;
    default:
        constants.push_back(termIt);
        break;
    }
}

void
XEquivalenceClass::merge(
    const XEquivalenceClass& eq )
{
    // Each equivalence class has an empty intersection with
    // other equivalence classes from the same partition.
    // Thus, checking for double insertions is useless.
    for( unsigned i=0; i<eq.standardVars.size(); i++ )
        pushTerm(eq.standardVars[i],Variable);
    for( unsigned i=0; i<eq.frontierVars.size(); i++ )
        pushTerm(eq.frontierVars[i],FrontierVariable);
    for( unsigned i=0; i<eq.existentialVars.size(); i++ )
        pushTerm(eq.existentialVars[i],ExistentialVariable);
    for( unsigned i=0; i<eq.constants.size(); i++ )
        pushTerm(eq.constants[i],Constant);
}

bool
XEquivalenceClass::isValid() const
{
    if( constants.size() > 1 )
        return false;
    if( existentialVars.size() > 1 )
        return false;
    if( constants.size() > 0 && existentialVars.size() > 0 )
        return false;
    if( frontierVars.size() > 0 && existentialVars.size() > 0 )
        return false;
    return true;
}

const XTerm&
XEquivalenceClass::getRepresentativeTerm()
{
    if( constants.size() > 0 )
        return constants[0]->first;
    if( representativeTerm == NULL )
    {
        stringstream ss;
        program.incrementVariablesCounter();
        ss << "X" << program.getVariablesCounter();
        representativeTerm = program.createStandardVariable(ss.str());
    }
    return *representativeTerm;
}

const XEquivalenceClass::XPartitionMapIterator&
XEquivalenceClass::at(
    index_t index ) const
{
    assert_msg( ( index >= 0 && index < size() ), "Index out of range" );
    if( index < standardVars.size() )
        return standardVars[index];
    else if( index < standardVars.size() + frontierVars.size() )
        return frontierVars[index-standardVars.size()];
    else if( index < standardVars.size() + frontierVars.size() + existentialVars.size() )
        return existentialVars[index-(standardVars.size()+frontierVars.size())];
    else // if ( index < size() ) --> this should be the default case.
        return constants[index-(standardVars.size()+frontierVars.size()+existentialVars.size())];
}

XTermType
XEquivalenceClass::typeOfElementAt(
    index_t index ) const
{
    assert_msg( ( index >= 0 && index < size() ), "Index out of range" );
    if( index < standardVars.size() )
        return Variable;
    else if( index < standardVars.size() + frontierVars.size() )
        return FrontierVariable;
    else if( index < standardVars.size() + frontierVars.size() + existentialVars.size() )
        return ExistentialVariable;
    else // if ( index < size() ) --> this should be the default case.
        return Constant;
}

size_t
XEquivalenceClass::size() const
{
    return constants.size()+existentialVars.size()+frontierVars.size()+standardVars.size();
}
