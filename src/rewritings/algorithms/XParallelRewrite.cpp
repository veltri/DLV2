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
 * File:   XParallelRewrite.cpp
 * Author: pierfrancesco
 *
 * Created on 26 giugno 2015, 18.51
 */

#include "XParallelRewrite.h"

#include "../data/XParallelRulesetStandard.h"
#include "../data/XParallelRulesetSub.h"
#include "../data/XParallelRulesetNonSub.h"
#include "../../util/Trace.h"
#include "../../util/Options.h"
#include "../../util/Constants.h"
#include "../data/XHead.h"
#include "../data/XPieceUnifier.h"

#include <pthread.h>

using namespace DLV2::REWRITERS;
using namespace std;

std::vector< XRule* >
XParallelRewrite::rewrite()
{
    auto sTime = std::chrono::high_resolution_clock::now();
    assert_msg( inputProgram.getQuery() != NULL, "The input query is null." );
    trace_msg( rewriting, 1, "Start by adding the input query rules to the final rewriting: " );

    inputProgram.computePredicateNullsets();

    // The following iterator will be destroyed by "rewriteQueries".
    XParallelRuleset* rulesetIterator = new XParallelRulesetStandard(inputProgram);
    vector< XRule* > rewriting;
    addInputQueries(rewriting);
    rewritingSize = rewriting.size();
    rewriteQueries(rewriting,rulesetIterator,rewriting);

    // Before returning, erase eventual rules containing atoms "aux_X" where X is an int, because they might be
    // added by some DL2Datalog translators in order to normalize conjunctive heads.
    // Notice that, erasing elements from a vector is expensive, thus it is worth creating a new vector from scratch.
    vector< XRule* > rewritingWithoutAuxAtoms;
    eraseQueryWithAuxPreds(rewriting,rewritingWithoutAuxAtoms);

    auto eTime = std::chrono::high_resolution_clock::now();
    rewritingDuration = ( eTime - sTime );
    rewritingSize = rewriting.size();
    return rewritingWithoutAuxAtoms;
}

void
XParallelRewrite::rewriteQueries(
    const vector< XRule* >& queries,
    XParallelRuleset* rulesetIterator,
    vector< XRule* >& output )
{
    vector< XRule* > localRewriting;
    for( unsigned i=0; i<queries.size(); i++ )
    {
        const XRule& query = *queries[i];
        trace_msg( rewriting, 2, "Analyzing query " << query );
        // If the input query is atomic it is rewritten immediately, a splitability check is carried out otherwise.
        // If the query is splittable, a fresh query is generated for each independent component.
        // If the query is not splittable, it is managed by function rewriteConjunctiveQuery.
        if( query.getBody()->size() == 1 )
        {
            rewriteAtomicQuery(query,rulesetIterator,localRewriting);
        }
        else
        {
            // Try to split the query. If you manage to do that, do not forget to add a merging rule.
            const XBody* queryBody = query.getBody();
            assert_msg( queryBody != NULL, "Null body" );

            vector< XLiteral > mergeQueryBodyLiterals;
            unordered_set< unsigned > checkedBodyPositions;
            for( unsigned x=0; x<queryBody->size() && checkedBodyPositions.size()<queryBody->size(); x++ )
            {
                pair< unordered_set< unsigned >::const_iterator, bool > par = checkedBodyPositions.insert(x);
                if( par.second )
                {
                    XRandomAccessSet< index_t > sharedNulls;
                    XRandomAccessSet< unsigned > subQueryAtomPositions;
                    subQueryAtomPositions.pushItem(x);
                    for( unsigned y=0; y<subQueryAtomPositions.size(); y++ )
                    {
                        checkedBodyPositions.insert(subQueryAtomPositions[y]);
                        checkExistentialJoins(query,subQueryAtomPositions[y],subQueryAtomPositions,sharedNulls);
                    }
                    // If joinAtomsPositions has got the same size as the query body, the current query is
                    // composed by a unique conjunctive component.
                    if( subQueryAtomPositions.size() == queryBody->size() )
                    {
                        trace_msg( rewriting, 2, "The query is not decomposable" );
                        // FIXME
                        rewriteConjunctiveQuery(query,rulesetIterator,output);
                    }
                    // Else the current component may be either atomic or conjunctive.
                    else
                    {
                        trace_msg( rewriting, 2, "Existential join-decomposition..." );
                        assert_msg( sharedNulls.size() == 0, "Non-empty set of shared nulls." );
                        XRule* queryRule = generateSubQuery(query,subQueryAtomPositions,mergeQueryBodyLiterals);
                        // No need to check the existence of homomorphic queries since the head of this query is completely new.
                        // No need to carry out the query-elimination optimization check since the body of this query is atomic.
                        localRewriting.push_back(queryRule);
                    }
                }
            }
            if( mergeQueryBodyLiterals.size() > 0 )
            {
                // The variable renaming is not needed here since the following rule is not gonna be rewritten.
                const XHead* queryHead = query.getHead();
                assert_msg( queryHead != NULL, "Null head" );
                assert_msg( queryHead->isAtomic(), "Non-atomic head" );
                XHead* mergeQueryHead = inputProgram.createAtomicHead(queryHead->at(0));
                XBody* mergeQueryBody = inputProgram.createBody(mergeQueryBodyLiterals);
                XRule* mergeQuery = inputProgram.createRule(mergeQueryHead,mergeQueryBody);
                trace_msg( rewriting, 2, "The reconciliation rule is " << *mergeQuery );
                // This query mustn't be rewritten since its body predicates do not belong to the input program.
                output.push_back(mergeQuery);
            }
        }
    }
    // Our homomorphism check has been already carried out (the map of canonically-renamed queries is shared).
    for( XRule* rule : localRewriting )
    {
        output.push_back(rule);
        rewritingSize++;
        // TODO
        // Run a new thread on the current query.
        vector< XRule* > input;
        input.push_back(rule);
        // Every thread has to receive its own iterator.
        XParallelRuleset* threadRuleset = NULL;
        if( XParallelRulesetStandard* ptr = dynamic_cast< XParallelRulesetStandard* >(rulesetIterator) )
            threadRuleset = new XParallelRulesetStandard(*ptr);
        else if( XParallelRulesetSub* ptr = dynamic_cast< XParallelRulesetSub* >(rulesetIterator) )
            threadRuleset = new XParallelRulesetSub(*ptr);
        else if( XParallelRulesetNonSub* ptr = dynamic_cast< XParallelRulesetNonSub* >(rulesetIterator) )
            threadRuleset = new XParallelRulesetNonSub(*ptr);
        assert_msg( threadRuleset != NULL, "Null ruleset iterator!" );
        rewriteQueries(input,threadRuleset,output);
    }
    delete rulesetIterator;
}

void
XParallelRewrite::rewriteAtomicQuery(
    const XRule& query,
    XParallelRuleset* rulesetIterator,
    vector< XRule* >& output )
{
    assert_msg( query.getBody() != NULL, "Null body" );
    assert_msg( query.getHead() != NULL, "Null head" );
    assert_msg( query.getHead()->size() == 1, "Query rules with more than one head atom are not allowed" );
    // TODO: Fix statistics-variables..
//    auto sTime = std::chrono::high_resolution_clock::now();
//    assert_msg( inputProgram.getQuery() != NULL, "The input query is null." );
    // TODO: Fix tracing..
//    trace_msg( rewriting, 1, "Start by adding the input query rules to the final rewriting: " );

    while( rulesetIterator->hasNext() )
    {
        const XRule& rule = rulesetIterator->next();
        trace_msg( rewriting, 2, "Computing single-piece unifiers between " << query << " and " << rule );
        std::list< XRule > tmpRules4AggrUnifiers;
        // NOTICE: This function is responsible for the deallocation of the following pointers.
        vector< XPieceUnifier* > SPU = computeSPU(query,rule);
        // Extend SPU by computing the set of all single-piece aggregators of the
        // input query with the starting set of TGDs.
        computeSPUAggregators(SPU,tmpRules4AggrUnifiers);
        // Now, apply SPUs in order to produce new rewriting rules.
        for( unsigned x=0; x<SPU.size(); x++ )
        {
            assert_msg( SPU[x] != NULL, "Null unifier" );
            XRule* rewrittenRule = produceRewritingByPieceUnifier(*(SPU[x]));
            pushRewriting(rewrittenRule,output);
            delete SPU[x];
        }
        // Delete the aggregated rules added to the program in order to compute the aggregated single piece unifiers.
        tmpRules4AggrUnifiers.clear();
    }
    rulesetIterator->reset();
//    auto eTime = std::chrono::high_resolution_clock::now();
//    rewritingDuration = ( eTime - sTime );
//    rewritingSize = finalRewritingWithoutAuxAtoms.size();
}

void
XParallelRewrite::rewriteConjunctiveQuery(
    const XRule& query,
    XParallelRuleset* rulesetIterator,
    std::vector< XRule* >& output )
{
    // TODO
    vector< XProgram::const_iterator > exRules;
}

void
XParallelRewrite::checkExistentialJoins(
    const XRule& query,
    unsigned currentLiteralPos,
    XRandomAccessSet< unsigned >& subQueryAtomPositions,
    XRandomAccessSet< index_t >& sharedNulls ) const
{
    // For each term from the current literal and for each (body) position where it occurs
    // check whether such a position is relative to a different atom and whether an existential-join could hold.
    assert_msg( query.getBody() != NULL, "Null body" );
    assert_msg( currentLiteralPos < query.getBody()->size(), "Index out of range" );
    const XNullsetTable& nullsetTable = inputProgram.getPredicateNullsets();
    const XLiteral& currentLiteral = query.getBody()->at(currentLiteralPos);
    trace_msg( rewriting, 2, "Check whether literal " << currentLiteral << " has got some existential-joins."  );
    for( unsigned i=0; i<currentLiteral.getTerms().size(); i++ )
    {
        const XTerm& currentTerm = currentLiteral.getTerms().at(i);
        for( unsigned j=0; j<query.getBodyPositions(currentTerm).size(); j++ )
        {
            unsigned joinLiteralPos = query.getBodyPositions(currentTerm).at(j).atomPos;
            unsigned joinTermPos = query.getBodyPositions(currentTerm).at(j).termPos;
            assert_msg( joinLiteralPos < query.getBody()->size(), "Index out of range" );
            assert_msg( joinTermPos < query.getBody()->at(joinLiteralPos).getTerms().size(), "Index out of range" );
            // The previous literals have been already processed, so consider just the following ones
            // (which might belong to another sub-query). Anyway, given two atoms, a1 and a2, if a1 has got
            // an existential join with a2, then a2 has got an existential join with a1.
            // Thus, no problems if literals from the other sub-queries are considered here.
            if( joinLiteralPos > currentLiteralPos )
            {
                const XLiteral& joinLiteral = query.getBody()->at(joinLiteralPos);
                const XNullset& currentPositionNullset = nullsetTable.at(currentLiteral.getPredIndex()).at(i);
                const XNullset& joinPositionNullset = nullsetTable.at(joinLiteral.getPredIndex()).at(joinTermPos);
                for( unsigned k=0; k<currentPositionNullset.size(); k++ )
                {
                    if( joinPositionNullset.find(currentPositionNullset[k]) )
                    {
                        trace_msg( rewriting, 3, "An existential-join (null_id: " << currentPositionNullset[k] << ")" <<
                                " may hold between " << joinLiteral << "_" << joinTermPos << " and " << currentLiteral << "_" << i );
                        sharedNulls.pushItem(currentPositionNullset[k]);
                        subQueryAtomPositions.pushItem(joinLiteralPos);
                    }
                }
            }
        }
    }
}

XRule*
XParallelRewrite::generateSubQuery(
    const XRule& query,
    const XRandomAccessSet< unsigned >& subQueryAtomPositions,
    vector< XLiteral >& mergeQueryBodyLiterals )
{
    const XBody* queryBody = query.getBody();
    assert_msg( queryBody != NULL, "Null body" );
    stringstream ss;
    // Compute the set of terms which are gonna be included by the head.
    vector< XTerm > subQueryHeadTerms;
    vector< XLiteral > subQueryBodyLiterals;
    vector< XTerm > mergeQueryBodyAtomTerms;
    // The subquery needs to be renamed since it will be processed by the rewriting algorithm.
    // The same does not hold for the merging query, which will not be rewritten.
    XMapping renaming;
    for( unsigned i=0; i<subQueryAtomPositions.size(); i++ )
    {
        const XLiteral& literal = queryBody->at(subQueryAtomPositions[i]);
        vector< XTerm > subQueryBodyAtomTerms;
        for( unsigned j=0; j<literal.getTerms().size(); j++ )
        {
            const XTerm& term = literal.getTerms().at(j);
            if( term.isStandardVar() )
            {
                XMapping::const_iterator it = renaming.find(term);
                if( it == renaming.end() )
                {
                    stringstream ss;
                    // FIXME this is shared -> writelock!
                    inputProgram.incrementVariablesCounter();
                    ss << "X" << inputProgram.getVariablesCounter();
                    XTerm* renamedTerm = inputProgram.createStandardVariable(ss.str());
                    renaming.insert(pair< const XTerm&, const XTerm& >(term,*renamedTerm));
                    subQueryBodyAtomTerms.push_back(*renamedTerm);
                    // Include the current variable in the head if it is a distinguished variable from the original query
                    // (i.e., it belongs to the head or occurs in a body literal other than the ones belonging to the current subquery).
                    if( query.getHeadOccurrences(term) > 0 )
                    {
                        subQueryHeadTerms.push_back(*renamedTerm);
                        mergeQueryBodyAtomTerms.push_back(term);
                    }
                    else
                    {
                        bool isShared = false;
                        for( unsigned x=0; x<query.getBodyPositions(term).size() && !isShared; x++ )
                            if( !subQueryAtomPositions.find(query.getBodyPositions(term).at(x).atomPos) )
                            {
                                isShared = true;
                                subQueryHeadTerms.push_back(*renamedTerm);
                                mergeQueryBodyAtomTerms.push_back(term);
                            }
                    }
                    delete renamedTerm;
                }
                else
                {
                    subQueryBodyAtomTerms.push_back(it->second);
                }
            }
            else
            {
                subQueryBodyAtomTerms.push_back(literal.getTerms().at(j));
            }
        }
        XAtom* subQueryBodyAtom = inputProgram.createAtom(literal.getPredIndex(),subQueryBodyAtomTerms,literal.getAtom().isTrueNegated());
        XLiteral* subQueryBodyLiteral = inputProgram.createLiteral(*subQueryBodyAtom,literal.isNaf());
        subQueryBodyLiterals.push_back(*subQueryBodyLiteral);
        delete subQueryBodyAtom;
        delete subQueryBodyLiteral;
    }
    // FIXME queryPredIdx is shared, add a write-lock here...
    ss << QUERY_ANS << queryPredIdx++;
    pair< index_t, bool > resSubQueryPred = inputProgram.addPredicate(ss.str(),subQueryHeadTerms.size());
    // queryHeadAtom should include all the terms appearing in the body, which may be a conjunction.
    XAtom* subQueryHeadAtom = inputProgram.createAtom(resSubQueryPred.first,subQueryHeadTerms);
    XHead* subQueryHead = inputProgram.createAtomicHead(*subQueryHeadAtom);
    delete subQueryHeadAtom;
    XBody* subQueryBody = inputProgram.createBody(subQueryBodyLiterals);
    XRule* subQueryRule = inputProgram.createRule(subQueryHead,subQueryBody);
    trace_msg( rewriting, 2, "The generated existentially-decomposed sub-query is " << *subQueryRule );
    // Before returning update mergeQueryBodyLits
    XAtom* mergeQueryBodyAtom = inputProgram.createAtom(resSubQueryPred.first,mergeQueryBodyAtomTerms);
    XLiteral* mergeQueryBodyLiteral = inputProgram.createLiteral(*mergeQueryBodyAtom);
    mergeQueryBodyLiterals.push_back(*mergeQueryBodyLiteral);
    trace_msg( rewriting, 2, "Add " << *mergeQueryBodyLiteral << " to the merging rule." );
    delete mergeQueryBodyAtom;
    delete mergeQueryBodyLiteral;

    return subQueryRule;
}
