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

#include "DBRule.h"
#include <vector>

using namespace std;
using namespace DLV2::DB;
    
DBRule::DBRule(
    const vector<DBAtom*>& h, 
    const vector<DBLiteral*>& b,
    bool neg,
    bool aggr,
    bool built ):
        head(h),
        body(b),
        negation(neg),
        aggregates(aggr),
        builtins(built)
{
}

DBRule::DBRule(
    const DBRule& rule ):
        head(rule.head),
        body(rule.body),
        negation(rule.negation),
        aggregates(rule.aggregates),
        builtins(rule.builtins)
{
}

DBRule::~DBRule()
{
    for( unsigned i=0; i<head.size(); i++ )
    {
        assert_msg( head[i] != NULL, "Trying to destroy a rule with a null head atom." );
        delete head[i];
    }
    for( unsigned i=0; i<body.size(); i++ )
    {
        assert_msg( body[i] != NULL, "Trying to destroy a rule with a null body literal." );
        delete body[i];
    }
}