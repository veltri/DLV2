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

#include "DBPredicateNames.h"
#include "../../util/Assert.h"

using namespace DLV2::DB;
using namespace std;

DBPredicateNames::DBPredicateNames( 
    const DBPredicateNames& pn2 ):
        startIndex(pn2.startIndex),
        preds(pn2.preds), 
        internal(pn2.internal)
{
    // There is no good reason why this structure should be copied.
    assert(0);
}

DBPredicateNames& 
DBPredicateNames::operator=(
    const DBPredicateNames& pn2 )
{
    // There is no good reason why this structure should be copied.
    assert(0);

    if( this != &pn2 )
        {
        preds = pn2.preds;
        internal = pn2.internal;
        }

    return *this;
}

pair< index_t, bool > 
DBPredicateNames::add(
    const char* name, 
    unsigned arity,
    bool isInternal )
{
    pair< index_t, bool > addResult = preds.add(DBNamesItem(name,arity));
    if(addResult.second)
    {
        // A new name.
        assert_msg( addResult.first == internal.size(), 
                "The predicate's index does not match" );
        internal.push_back(isInternal);
    }
    return addResult;
}

pair< index_t, bool > 
DBPredicateNames::add( 
    const std::string& name, 
    unsigned arity, 
    bool isInternal )
{
    pair< index_t, bool > addResult = preds.add(DBNamesItem(name,arity));
    if(addResult.second)
    {
        // A new name.
        assert_msg( addResult.first == internal.size(), 
                "The predicate's index does not match" );
        internal.push_back(isInternal);
    }
    return addResult;    
}

unsigned
DBPredicateNames::getArity(
    index_t index ) const
{
    assert_msg( index < preds.size(), "Index out of range" );
    return preds.getItem(index).getArity();
}

const string&
DBPredicateNames::getName(
    index_t index ) const
{
    assert_msg( index < preds.size(), "Index out of range" );
    return preds.getItem(index).getNameAsString();
}

bool 
DBPredicateNames::isInternal(
    index_t index ) const
{
    assert_msg( index < internal.size(), "Index out of range" );
    return internal[index];
}

void 
DBPredicateNames::print(
    index_t index, 
    ostream& o ) const 
{
    assert_msg( index < preds.size(), "Index out of range" );
    o << preds.getItem(index);
}

const DBNamesItem& 
DBPredicateNames::getItem(
    index_t index ) const
{
    assert_msg( index < preds.size(), "Index out of range" );
    return preds.getItem(index);
}