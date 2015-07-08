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

XRule::XRule():
        head(NULL),
        body(NULL),
        termsMetadata(),
        naf(false),
        recursive(false),
        hasExistentialVars(false),
        hasFrontierVars(false),
        existVars()
{
    assert(0);
}

XRule::XRule(
    XHead* h,
    XBody* b ):
        head(h),
        body(b),
        naf(-1),
        recursive(-1)
{
    assert_msg( head != NULL, "Rules must have at least the head" );
    hasExistentialVars = false;
    hasFrontierVars = false;
    // Count the occurrences of each variable.
    for( unsigned i=0; i<head->size(); i++ )
    {
        const XAtom& atom = head->at(i);
        // The following is an auxiliary set, it'll be used to check
        // whether a variable has been already seen in the same literal.
        unordered_set< XTerm > atomVars;
        for( unsigned j=0; j<atom.getTerms().size(); j++ )
        {
            const XTerm& term = atom.getTerms().at(j);
            if( term.isStandardVar() )
            {
                XCoordinates headCoordinates;
                headCoordinates.atomPos = i;
                headCoordinates.termPos = j;

                // If the variable has already an associated metadata, that won't be overwritten.
                pair< XTermMetadataMap::iterator, bool > lookUp =
                        termsMetadata.insert(pair< const XTerm&, const XTermMetadata& >(term,XTermMetadata(term)));
                existVars.insert(term);

                // Store the current position of the variable.
                XTermMetadataMap::iterator termMetadataIt = lookUp.first;
                termMetadataIt->second.addHeadPosition(headCoordinates);

                // Check whether the current variable has been already seen in the current literal.
                pair< typename unordered_set< XTerm >::const_iterator, bool > firstOccurrence =
                        atomVars.insert(term);
                if( firstOccurrence.second )
                {
                    // Increment the occurrenceCounter of the current variable.
                    termMetadataIt->second.incrementHeadOccurrences();
                }
            }
        }
    }

    if( body != NULL )
    {
        for( unsigned i=0; i<body->size(); i++ )
        {
            const XAtom& atom = body->at(i).getAtom();
            // The following is a support set, it'll be used to understand
            // whether a variable has been already seen in the same literal.
            unordered_set< XTerm > atomVars;
            for( unsigned j=0; j<atom.getTerms().size(); j++ )
            {
                const XTerm& term = atom.getTerms().at(j);
                if( term.isStandardVar() )
                {
                    XCoordinates bodyCoordinates;
                    bodyCoordinates.atomPos = i;
                    bodyCoordinates.termPos = j;

                    // If the variable has already an associated metadata, that won't be overwritten.
                    pair< XTermMetadataMap::iterator, bool > lookUp =
                            termsMetadata.insert(pair< const XTerm&, const XTermMetadata& >(term,XTermMetadata(term)));
                    existVars.erase(term);
                    // If the element is not new and this is its first occurrence in the body, it is a frontier variable.
                    if( !lookUp.second && lookUp.first->second.getBodyOccurrences() == 0 )
                        hasFrontierVars = true;

                    // Store the current position of the variable.
                    XTermMetadataMap::iterator termMetadataIt = lookUp.first;
                    termMetadataIt->second.addBodyPosition(bodyCoordinates);

                    // Check whether the current variable has been already seen in the current literal.
                    pair< typename unordered_set< XTerm >::const_iterator, bool > firstOccurrence =
                            atomVars.insert(term);
                    if( firstOccurrence.second )
                    {
                        // Increment the occurrenceCounter of the current variable.
                        termMetadataIt->second.incrementBodyOccurrences();
                    }
                }
            }
        }
    }

    if( existVars.size() > 0 )
        hasExistentialVars = true;
}

XRule::XRule(
    const XRule& rule ):
        termsMetadata(rule.termsMetadata),
        naf(rule.naf),
        recursive(rule.recursive),
        hasExistentialVars(rule.hasExistentialVars),
        hasFrontierVars(rule.hasFrontierVars),
        existVars(rule.existVars)
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
    assert_msg( recursive != -1, "Can't establish whether the rule is recursive at the moment" );
    return recursive;
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


bool
XRule::isExistential(
    const XTerm& var ) const
{
    if( var.isStandardVar() )
    {
        XTermMetadataMap::const_iterator it =
                termsMetadata.find(var);
        assert_msg( it != termsMetadata.end(), "Variable not mapped" );
        return ( it->second.getHeadOccurrences() > 0 && it->second.getBodyOccurrences() == 0 );
    }
    return false;
}

bool
XRule::isFrontier(
    const XTerm& var ) const
{
    if( var.isStandardVar() )
    {
        XTermMetadataMap::const_iterator it =
                termsMetadata.find(var);
        assert_msg( it != termsMetadata.end(), "Variable not mapped" );
        return ( it->second.getHeadOccurrences() > 0 && it->second.getBodyOccurrences() > 0 );
    }
    return false;
}


const std::vector< XCoordinates >&
XRule::getHeadPositions(
    const XTerm& term ) const
{
    XTermMetadataMap::const_iterator it =
            termsMetadata.find(term);
    assert_msg( it != termsMetadata.end(), "Not valid term" );
    return it->second.getHeadPositions();
}

const vector< XCoordinates >&
XRule::getBodyPositions(
    const XTerm& term ) const
{
    XTermMetadataMap::const_iterator it =
            termsMetadata.find(term);
    assert_msg( it != termsMetadata.end(), "Not valid term" );
    return it->second.getBodyPositions();
}

unsigned
XRule::getHeadOccurrences(
    const XTerm& term ) const
{
    XTermMetadataMap::const_iterator it =
            termsMetadata.find(term);
    if( it != termsMetadata.end() )
        return it->second.getHeadOccurrences();
    else
        return 0;
}

unsigned
XRule::getBodyOccurrences(
    const XTerm& term ) const
{
    XTermMetadataMap::const_iterator it =
            termsMetadata.find(term);
    if( it != termsMetadata.end() )
        return it->second.getBodyOccurrences();
    else
        return 0;
}

bool
XRule::isMarked(
    const XTerm& term ) const
{
    XTermMetadataMap::const_iterator it =
            termsMetadata.find(term);
    if( it != termsMetadata.end() )
        return it->second.isStickyMarked();
    else
        return false;
}

void
XRule::markVariable(
    const XTerm& term )
{
    XTermMetadataMap::iterator it =
            termsMetadata.find(term);
    assert_msg( it != termsMetadata.end(), "Not valid variable" );
    it->second.setStickyMarked(true);
}

bool
XRule::operator==(
    const XRule& rule ) const
{
    assert_msg( head != NULL, "Null head" );
    if( *head == *(rule.head) )
    {
        if( body != NULL && rule.body != NULL && *body == *(rule.body) )
            return true;
        else if( body == NULL && rule.body == NULL )
            return true;
    }
    return false;
}

bool
XRule::operator!=(
    const XRule& rule ) const
{
    return !(*this == rule);
}
