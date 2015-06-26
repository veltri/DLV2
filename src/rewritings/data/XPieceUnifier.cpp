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
 * File:   XPieceUnifier.cpp
 * Author: pierfrancesco
 *
 * Created on 31 gennaio 2015, 15.15
 */

#include "XPieceUnifier.h"

#include "XPartition.h"
#include "../../util/Assert.h"
#include "../../util/Trace.h"
#include "../../util/Options.h"

using namespace std;
using namespace DLV2::REWRITERS;

XPieceUnifier::XPieceUnifier(
    const vector< XAtom >& q,
    const vector< XAtom >& h,
    XPartition* p,
    const XRule& query,
    const XRule& rule,
    const unordered_set< unsigned >& subQueryPositions ):
        subQuery(q),
        subHead(h),
        partition(p),
        originalQuery(query),
        originalRule(rule),
        subQueryAtomPositions(subQueryPositions),
        stickyVariables(),
        stickyVariablesComputed(false)
{
    assert_msg( p != NULL, "Null partition" );
}

XPieceUnifier::XPieceUnifier(
    const XPieceUnifier& p ):
        subQuery(p.subQuery),
        subHead(p.subHead),
        originalQuery(p.originalQuery),
        originalRule(p.originalRule),
        subQueryAtomPositions(p.subQueryAtomPositions),
        stickyVariables(p.stickyVariables),
        stickyVariablesComputed(p.stickyVariablesComputed)
{
    assert_msg( p.partition != NULL, "Null partitions are not allowed"  );
    partition = new XPartition(*p.partition);
}

XPieceUnifier::~XPieceUnifier()
{
    assert_msg( partition != NULL, "Null partitions are not allowed" );
    delete partition;
}

const unordered_set< XTerm >&
XPieceUnifier::getStickyVariables()
{
    // Sticky variables are the separating variables (those variables
    // which are in join between at least one atom of the sub-query, q',
    // and one atom of the query that is not in q') that occur in a class
    // of the partition containing an existential variable of the rule.
    if( !stickyVariablesComputed )
    {
        trace_msg( rewriting, 4, "Compute the set of sticky variables" );
        for( unsigned i=0; i<subQuery.size(); i++ )
        {
            for( unsigned j=0; j<subQuery[i].getTerms().size(); j++ )
            {
                const XTerm& currentTerm = subQuery[i].getTerms().at(j);
                if( currentTerm.isStandardVar() )
                {
                    bool likelyToBeSticky = false;
                    // Actually this check should be useless because every query rule should have an atomic propositional head.
                    if( originalQuery.getHeadPositions(currentTerm).size() > 0 )
                    {
                        trace_msg( rewriting, 4, "" << currentTerm << " is a separating variable since it occurs in the head" );
                        likelyToBeSticky = true;
                    }

                    // Current term may be a sticky variables just whether it appears in an atom which
                    // does not belong to the current sub-query.
                    const vector< XCoordinates >& bodyPositions = originalQuery.getBodyPositions(currentTerm);
                    for( unsigned k=0; k<bodyPositions.size() && !likelyToBeSticky; k++ )
                    {
                        // Checking whether currentTerm occurs also out of the subquery is enough to figure out whether it occurs in
                        // a different atom, because the current occurrence is in the subquery for sure.
                        unordered_set< unsigned >::iterator isInTheSubQuery = subQueryAtomPositions.find(bodyPositions[k].atomPos);
                        if( isInTheSubQuery == subQueryAtomPositions.end() )
                        {
                            trace_msg( rewriting, 4,
                                    "" << currentTerm << " is a separating variable since it occurs in body atom " << originalQuery.getBody()->at(bodyPositions[k].atomPos) );
                            likelyToBeSticky = true;
                        }
                    }
                    assert_msg( partition != NULL, "Null partition" );
                    if( likelyToBeSticky && partition->isPartitionedWithAnExistentialVariable(currentTerm) )
                        stickyVariables.insert(currentTerm);
                }
            }
        }
        stickyVariablesComputed = true;
    }
    return stickyVariables;
}

bool
XPieceUnifier::isThisSubQueryDisjointWith(
    const XPieceUnifier& p ) const
{
    assert_msg( this->originalQuery == p.originalQuery, "These unifiers belong to different query" );
    for( unordered_set< unsigned >::const_iterator it = subQueryAtomPositions.begin(); it != subQueryAtomPositions.end(); it++ )
        if( p.getSubQueryAtomPositions().find(*it) != p.getSubQueryAtomPositions().end() )
            return false;

    return true;
}

void
XPieceUnifier::extendThisIsNotSinglePiece(
    const vector< XAtom >& subQ,
    const vector< XAtom >& subH,
    const unordered_set< unsigned >& subQueryPos )
{
    // A piece unifier is always extended by adding just different atoms,
    // thus checking for multiple additions of the same atom is unnecessary.
    for( unsigned i=0; i<subQ.size(); i++ )
        subQuery.push_back(subQ[i]);
    for( unsigned i=0; i<subH.size(); i++ )
        subHead.push_back(subH[i]);
    subQueryAtomPositions.insert(subQueryPos.begin(),subQueryPos.end());
    // In this case, re-computing the set of sticky variables is necessary.
    stickyVariablesComputed = false;
}
