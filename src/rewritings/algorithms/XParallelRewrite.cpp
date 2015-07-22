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
#include "../../util/Trace.h"
#include "../../util/Options.h"
#include "../../util/Constants.h"
#include "../data/XHead.h"
#include "../data/XPieceUnifier.h"

using namespace DLV2::REWRITERS;
using namespace std;

std::vector< XRule* >
XParallelRewrite::rewrite()
{
    auto sTime = std::chrono::high_resolution_clock::now();
    assert_msg( inputProgram.getQuery() != NULL, "The input query is null." );
    trace_msg( rewriting, 1, "Start by adding the input query rules to the final rewriting: " );

    inputProgram.computePredicateNullsets();
    const XNullsetTable& predNullsets = inputProgram.getPredicateNullsets();

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
    delete rulesetIterator;
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
//        if( query.getBody()->size() == 1 ) // Atomic query
        {
            rewriteAtomicQuery(query,rulesetIterator,localRewriting);
        }
//        else
//        {
//            if( isBreakable(query) )
//            {
//                // Break the body of the current query and run a fresh thread for each component. Finally, add a merging rule.
//                const XBody* queryBody = query.getBody();
//                assert_msg( queryBody != NULL, "Null body" );
//
//                vector< XLiteral > mergingQueryBodyContainer;
//                for( unsigned x=0; x<queryBody->size(); x++ )
//                {
//                    stringstream ss;
//                    // FIXME queryPredIdx is shared, add a write-lock here...
//                    ss << QUERY_ANS << queryPredIdx++;
//                    pair< index_t, bool > resQueryPred = inputProgram.addPredicate(ss.str(),queryBody->at(x).getTerms().size());
//                    XAtom* queryHeadAtom = inputProgram.createAtom(resQueryPred.first,queryBody->at(x).getTerms());
//                    XHead* queryHead = inputProgram.createAtomicHead(*queryHeadAtom);
//                    mergingQueryBodyContainer.push_back(*queryHeadAtom);
//                    delete queryHeadAtom;
//                    vector< XLiteral > queryBodyContainer;
//                    queryBodyContainer.push_back(queryBody->at(x));
//                    XBody* queryBody = inputProgram.createBody(queryBodyContainer);
//                    XRule* queryRule = inputProgram.createRule(queryHead,queryBody);
//                    // No need to check the existence of homomorphic queries since the head of this query is completely new.
//                    // No need to carry out the query-elimination optimization check since the body of this query is atomic.
//                    localRewriting.push_back(queryRule);
//                }
//                const XHead* queryHead = query.getHead();
//                assert_msg( queryHead != NULL, "Null head" );
//                assert_msg( queryHead->isAtomic(), "Non-atomic head" );
//                XHead* mergingQueryHead = inputProgram.createAtomicHead(queryHead->at(0));
//                XBody* mergingQueryBody = inputProgram.createBody(mergingQueryBodyContainer);
//                XRule* mergingQuery = inputProgram.createRule(mergingQueryHead,mergingQueryBody);
//                // This query mustn't be rewritten since its body predicates do not belong to the input program.
//                output.push_back(mergingQuery);
//            }
//            else
//            {
//                // TODO
//            }
//        }
    }
    // Our homomorphism check has been already carried out (the map of canonically-renamed queries is shared).
    for( XRule* rule : localRewriting )
    {
        // FIXME isUnnecessary is working on a shared cache...
//        if( !isUnnecessary(*rule) )
        {
            output.push_back(rule);
            rewritingSize++;
            // TODO
            // Run a new thread on the current query.
            vector< XRule* > input;
            input.push_back(rule);
            rewriteQueries(input,rulesetIterator,output);
        }
//        else
//            delete rule;
    }
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

}

bool
XParallelRewrite::isBreakable(
    const XRule& query ) const
{

}
