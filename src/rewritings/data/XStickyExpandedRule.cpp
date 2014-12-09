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
 * File:   XStickyExpandedRule.cpp
 * Author: pierfrancesco
 *
 * Created on 05 novembre 2014, 13.10
 */

#include "XStickyExpandedRule.h"

using namespace std;
using namespace DLV2::REWRITERS;

XStickyExpandedRule::XStickyExpandedRule(
    const XStickyExpandedRule& expRule ):
        rule(expRule.rule),
        labels(expRule.labels),
        termsMetadata(expRule.termsMetadata)
{
}

XStickyExpandedRule::XStickyExpandedRule(
    const XRule& rul ):
        rule(rul),
        labels()
{
    const XHead* head = rule.getHead();
    assert_msg( head != NULL, "Null head" );
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
                XStickyCoordinates headCoordinates;
                headCoordinates.atomPos = i;
                headCoordinates.termPos = j;

                // If the variable has already an associated metadata, that won't be overwritten.
                pair< XStickyTermMetadataMap::iterator, bool > lookUp =
                        termsMetadata.insert(pair< const XTerm&, const XStickyTermMetadata& >(term,XStickyTermMetadata(term)));

                // Store the current position of the variable.
                XStickyTermMetadataMap::iterator termMetadataIt = lookUp.first;
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

    const XBody* body = rule.getBody();
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
                    XStickyCoordinates bodyCoordinates;
                    bodyCoordinates.atomPos = i;
                    bodyCoordinates.termPos = j;

                    // If the variable has already an associated metadata, that won't be overwritten.
                    pair< XStickyTermMetadataMap::iterator, bool > lookUp =
                            termsMetadata.insert(pair< const XTerm&, const XStickyTermMetadata& >(term,XStickyTermMetadata(term)));

                    // Store the current position of the variable.
                    XStickyTermMetadataMap::iterator termMetadataIt = lookUp.first;
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
}

const std::vector< XStickyCoordinates >&
XStickyExpandedRule::getHeadPositions(
    const XTerm& term ) const
{
    XStickyTermMetadataMap::const_iterator it =
            termsMetadata.find(term);
    assert_msg( it != termsMetadata.end(), "Not valid term" );
    return it->second.getHeadPositions();
}

const vector< XStickyCoordinates >&
XStickyExpandedRule::getBodyPositions(
    const XTerm& term ) const
{
    XStickyTermMetadataMap::const_iterator it =
            termsMetadata.find(term);
    assert_msg( it != termsMetadata.end(), "Not valid term" );
    return it->second.getBodyPositions();
}

unsigned
XStickyExpandedRule::getHeadOccurrences(
    const XTerm& term ) const
{
    XStickyTermMetadataMap::const_iterator it =
            termsMetadata.find(term);
    if( it != termsMetadata.end() )
        return it->second.getHeadOccurrences();
    else
        return 0;
}

unsigned
XStickyExpandedRule::getBodyOccurrences(
    const XTerm& term ) const
{
    XStickyTermMetadataMap::const_iterator it =
            termsMetadata.find(term);
    if( it != termsMetadata.end() )
        return it->second.getBodyOccurrences();
    else
        return 0;
}

bool
XStickyExpandedRule::isMarked(
    const XTerm& term ) const
{
    XStickyTermMetadataMap::const_iterator it =
            termsMetadata.find(term);
    if( it != termsMetadata.end() )
        return it->second.isMarked();
    else
        return false;
}

void
XStickyExpandedRule::markVariable(
    const XTerm& term )
{
    XStickyTermMetadataMap::iterator it =
            termsMetadata.find(term);
    assert_msg( it != termsMetadata.end(), "Not valid variable" );
    it->second.setMarked(true);
}
