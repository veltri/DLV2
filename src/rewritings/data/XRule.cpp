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
 * File:   XRule.cpp
 * Author: pierfrancesco
 *
 * Created on 29/ott/2014, 16:05:27
 */

#include "XRule.h"
#include "XConjunctiveHead.h"
#include "XDisjunctiveHead.h"
#include "XAtomicHead.h"
#include "../../util/ErrorMessage.h"

using namespace std;
using namespace DLV2::REWRITERS;

XRule::XRule(
    XHead* h,
    XBody* b ):
        head(h),
        body(b),
        naf(-1),
        recursion(-1)
{
    assert_msg( h != NULL, "Rules must have at least the head" );
}

XRule::XRule(
    const XRule& rule ):
        naf(rule.naf),
        recursion(rule.recursion)
{
    assert_msg( rule.head != NULL, "Null rule head" );
    try{
        if( rule.head->isAtomic() )
        {
            XAtomicHead* headPtr = dynamic_cast< XAtomicHead* >(rule.head);
            assert_msg( headPtr != NULL, "Atomic rule head not valid" );
            head = new XAtomicHead(*headPtr);
        }
        else if( rule.head->isDisjunctive() )
        {
            XDisjunctiveHead* headPtr = dynamic_cast< XDisjunctiveHead* >(rule.head);
            assert_msg( headPtr != NULL, "Disjunctive rule head not valid" );
            head = new XDisjunctiveHead(*headPtr);
        }
        else if( rule.head->isConjunctive() )
        {
            XConjunctiveHead* headPtr = dynamic_cast< XConjunctiveHead* >(rule.head);
            assert_msg( headPtr != NULL, "Conjunctive rule head not valid" );
            head = new XConjunctiveHead(*headPtr);
        }
        else
            assert(0);
    }
    catch( exception& e )
    {
        ErrorMessage::errorGeneric(e.what());
    }

    if( rule.body != NULL )
        body = new XBody(*rule.body);
}

XRule::~XRule()
{
    assert_msg( head != NULL, "Rules must have at least the head" );
    delete head;
    if( body )
        delete body;
}

bool
XRule::hasNegation()
{
    if( naf == -1 )
    {
        naf = 0;
        if( body != NULL )
        {
            for( unsigned i=0; i<body->size(); i++ )
                if( (*body)[i].isNaf() )
                    naf = 1;
        }
    }
    return naf;
}

bool
XRule::hasAtomicHead() const
{
    assert_msg( head != NULL, "Rules must have at least the head" );
    return head->isAtomic();
}

bool
XRule::hasDisjunctiveHead() const
{
    assert_msg( head != NULL, "Rules must have at least the head" );
    return head->isDisjunctive();
}

bool
XRule::hasConjunctiveHead() const
{
    assert_msg( head != NULL, "Rules must have at least the head" );
    return head->isConjunctive();
}

bool
XRule::isRecursive() const
{
    assert_msg( recursion != -1, "Can't establish whether the rule is recursive at the moment" );
    return recursion;
}

bool
XRule::isGround() const
{
    assert_msg( head != NULL, "Rules must have at least the head" );
    if( !head->isGround() )
            return false;
    if( body != NULL && !body->isGround() )
        return false;
    return true;
}
