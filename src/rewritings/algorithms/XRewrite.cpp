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
 * File:   XRewrite.cpp
 * Author: pierfrancesco
 *
 * Created on 10 dicembre 2014, 16.16
 */

#include "XRewrite.h"

#include "../../util/Assert.h"
#include "../../util/Trace.h"
#include "../../util/Options.h"
#include "../../util/Utils.h"
#include "../../util/Constants.h"
#include "../data/XHead.h"
#include "../data/XPieceUnifier.h"
#include "../data/XPartition.h"
#include "../data/XHomomorphismCache.h"
#include "../homomorphisms/IsomorphismCheckByWasp.h"

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>

using namespace DLV2::REWRITERS;
using namespace std;

XRewrite::XRewrite(
    XProgram& input ):
        RewritingAlgorithm(input),
        isomorphismStrategy(new IsomorphismCheckByWasp(input)),
        canonicalRuleHashCodesCache(),
        reachabilityCache(),
        homomorphismCache(input),
//        predicateNewQueryHeadAtom(0),
//        predicateOldQueryHeadAtom(0),
        rewritingDuration(0),
        rewritingSize(0),
        unifierAggregationDuration(0),
        queryNecessaryDuration(0),
        queryEliminationDuration(0),
        reachabilityDuration(0),
        homomorphismDuration(0)
{
}

XRewrite::~XRewrite()
{
    delete isomorphismStrategy;
}

vector< XRule* >
XRewrite::rewrite()
{
    auto sTime = std::chrono::high_resolution_clock::now();
    assert_msg( inputProgram.getQuery() != NULL, "The input query is null." );
    trace_msg( rewriting, 1, "Start by adding the input query rules to the final rewriting: " );

    vector< XRule* > finalRewriting;
    addInputQueries(finalRewriting);

    size_t oldSize = 0;
    size_t currentSize = finalRewriting.size();
    while( currentSize > oldSize )
    {
        trace_msg( rewriting, 1, "Iteration i^th:" );
        size_t i = oldSize;
        oldSize = finalRewriting.size();
        for( ; i<currentSize; i++ )
        {
            for( XProgram::const_iterator itRule = inputProgram.beginRules(); itRule != inputProgram.endRules(); itRule++ )
            {
                trace_msg( rewriting, 2, "Computing single-piece unifiers between " <<
                        *finalRewriting[i] << " and " << *itRule );
                // NOTICE: This function is responsible for the deallocation of the following pointers.
                vector< XPieceUnifier* > SPU = computeSPU(*finalRewriting[i],*itRule);
                // Extend SPU by computing the set of all single-piece aggregators of the
                // input query with the starting set of TGDs.
                computeSPUAggregators(SPU);
                // Now, apply SPUs in order to produce new rewriting rules.
                for( unsigned x=0; x<SPU.size(); x++ )
                {
                    assert_msg( SPU[x] != NULL, "Null unifier" );
                    XRule* rewrittenRule = produceRewritingByPieceUnifier(*(SPU[x]));
                    pushRewriting(rewrittenRule,finalRewriting);
                    delete SPU[x];
                }
                // Delete the aggregated rules added to the program in order to compute the aggregated single piece unifiers.
                inputProgram.eraseTemporaryRules();
            }
        }
        currentSize = finalRewriting.size();
    }

    // Before returning, erase eventual rules containing atoms "aux_X" where X is an int, because they are
    // added by some DL2Datalog translators in order to normalize conjunctive heads.
    // Notice that, erasing elements from a vector is expensive, thus it is worth creating a new vector from scratch.
    vector< XRule* > finalRewritingWithoutAuxAtoms;
    eraseQueryWithAuxPreds(finalRewriting,finalRewritingWithoutAuxAtoms);
    auto eTime = std::chrono::high_resolution_clock::now();
    rewritingDuration = ( eTime - sTime );
    rewritingSize = finalRewritingWithoutAuxAtoms.size();
    return finalRewritingWithoutAuxAtoms;
}

void
XRewrite::printStatistics() const
{
    cerr << endl << "***REWRITING STATISTICS***" << endl;
    cerr << "Rewriting time: " << rewritingDuration.count()/1000 << "s" << endl;
    cerr << "Rewriting size: " << rewritingSize << endl;
    cerr << "Unifier aggregation time: " << unifierAggregationDuration.count()/1000 << "s" << endl;
    cerr << "Query check time: " << queryNecessaryDuration.count()/1000 << "s" << endl;
    cerr << "Query elimination time: " << queryEliminationDuration.count()/1000 << "s" << endl;
    cerr << "Reachability time: " << reachabilityDuration.count()/1000 << "s" << endl;
    cerr << "Homomorphism time: " << homomorphismDuration.count()/1000 << "s" << endl;
}

void
XRewrite::pushRewriting(
    XRule* rewriting,
    vector< XRule* >& rewritings )
{
    // Check whether the generated rule is homomorphic to an existent one.
    bool isNecessary = !isUnnecessary(*rewriting);
    if( isNecessary )
    {
        // Finally, if the produced rule passes previous checks it is added to the final
        // rewriting, but just after being minimized by the query elimination strategy.
        XRule* optimizedQuery = queryElimination(*rewriting);
        if( optimizedQuery != NULL )
        {
            delete rewriting;
            // The optimized query may be different from the original one, so an additional check is required.
            bool isOptimizedQueryNecessary = !isUnnecessary(*optimizedQuery);
            if( isOptimizedQueryNecessary )
            {
                trace_msg( rewriting, 1, "Add query: " << *optimizedQuery );
                rewritings.push_back(optimizedQuery);
            }
            else
            {
                trace_msg( rewriting, 1, "Do not add query: " << *optimizedQuery );
                delete optimizedQuery;
            }
        }
        else
        {
            trace_msg( rewriting, 1, "Add query: " << *rewriting );
            rewritings.push_back(rewriting);
        }
    }
    else
    {
        trace_msg( rewriting, 1, "Do not add query: " << *rewriting );
        delete rewriting;
    }
}

void
XRewrite::addInputQueries(
    vector< XRule* >& finalRewriting )
{
    const XAtom* queryAtom = inputProgram.getQuery();
    // If the query is atomic, q(X,Y), add just the rule: QUERY_ANS(X,Y) :- q(X,Y).
    if( inputProgram.isQueryAtomic() )
    {
        // FIXME: the standard aspcore2.0 does not allow for existential variables in queries.
        // I mean, you can do it but you may introduce rules which don't enjoy the main properties
        // about decidability like for example stickiness, guardedness, and so on.
        pair< index_t, bool > resQueryPred = inputProgram.addPredicate(QUERY_ANS,0);
        XAtom* queryHeadAtom = inputProgram.createAtom(resQueryPred.first,vector< XTerm >());
        XHead* queryHead = inputProgram.createAtomicHead(*queryHeadAtom);
        delete queryHeadAtom;
        vector< XLiteral > queryBodyContainer;
        // Notice that, if the query is atomic, its predicate might be rewritten. Thus, the query atom
        // is to be moved to the body because the rewriting algorithm is able to work just on body atoms.
        XLiteral* queryBodyLiteral = inputProgram.createLiteral(*queryAtom);
        queryBodyContainer.push_back(*queryBodyLiteral);
        delete queryBodyLiteral;
        XBody* queryBody = inputProgram.createBody(queryBodyContainer);
        XRule* queryRule = inputProgram.createRule(queryHead,queryBody);
        // queryRule will be destroyed by the caller.
        pushRewriting(queryRule,finalRewriting);
    }
    else
    {
        for( XProgram::const_iterator it = inputProgram.beginQueryRules(); it != inputProgram.endQueryRules(); it++ )
        {
            // If the query is conjunctive, its head predicate appears only here. Thus, it will never be rewritten.
            assert_msg( it->getBody() != NULL, "Null body" );
            assert_msg( it->getHead() != NULL, "Null head" );
            assert_msg( it->getHead()->size() == 1, "Query rules with more than one head atom are not allowed" );
            XRule* queryRule = new XRule(*it);
            // queryRule will be destroyed by the caller.
            pushRewriting(queryRule,finalRewriting);
        }
    }
}

vector< XPieceUnifier* >
XRewrite::computeSPU(
    const XRule& query,
    const XRule& rule ) const
{
    vector< XPieceUnifier* > SPU;
    trace_msg( rewriting, 2, "Generate pre-unifiers first." );
    // NOTICE: This function is responsible for the destruction of the following pointers.
    // Since they won't be returned, they need to be deallocated at the end of the block.
    list< XPieceUnifier* > APU = computeAPU(query,rule);
    while( APU.size() > 0 )
    {
        trace_msg( rewriting, 3, "Processing pre-unifier: " << *(APU.front()) );
        // A pre-unifier is selected and extended in all possible ways with
        // other atomic pre-unifiers of APU.
        vector< XPieceUnifier* > currentExtendedPreUnifier = SPUext(query,rule,APU,APU.front());
        // NOTICE: The deallocation of these pointers is delegated to the caller.
        for( XPieceUnifier* currentUnifier : currentExtendedPreUnifier )
        {
            SPU.push_back(currentUnifier);
        }
        delete APU.front();
        APU.pop_front();
    }
    return SPU;
}

list< XPieceUnifier* >
XRewrite::computeAPU(
    const XRule& query,
    const XRule& rule ) const
{
    list< XPieceUnifier* > APU;
    assert_msg( query.getBody() != NULL, "Null query body" );
    assert_msg( rule.getHead() != NULL, "Null rule head" );
    assert_msg( !rule.getHead()->isDisjunctive(), "The algorithm does not work with disjunctive rules" );
    const XBody& queryBody = *query.getBody();
    const XHead& ruleHead = *rule.getHead();
    for( unsigned i=0; i<queryBody.size(); i++ )
    {
        for( unsigned j=0; j<ruleHead.size(); j++ )
        {
            trace_msg( rewriting, 3, "Looking for an APU between " << queryBody[i].getAtom() << " and " << ruleHead[j] );
            // if( queryBody[i].getAtom().getPredicateName() == ruleHead[j].getPredicateName() )
            if( queryBody[i].getAtom().getPredIndex() == ruleHead[j].getPredIndex() &&
                    queryBody[i].getAtom().getArity() == ruleHead[j].getArity() )
            {
                // Create the partition by position associated with { queryBody[j], ruleHead[i] }
                XPartition* partition = inputProgram.createPartition();
                createPartitionByPosition(queryBody[i].getAtom(),ruleHead[j],rule,*partition);
                if( partition->isValid() )
                {
                    vector< XAtom > queryAtoms;
                    queryAtoms.push_back(queryBody[i].getAtom());
                    vector< XAtom > ruleAtoms;
                    ruleAtoms.push_back(ruleHead[j]);
                    unordered_set< unsigned > subQueryAtomPositions;
                    subQueryAtomPositions.insert(i);
                    // The destruction of 'partition' is delegated to 'preUnifier'.
                    // The destruction of 'preUnifier' is delegated to the caller.
                    XPieceUnifier* preUnifier =
                            inputProgram.createPieceUnifier(queryAtoms,ruleAtoms,partition,query,rule,subQueryAtomPositions);
                    APU.push_back(preUnifier);
                    trace_msg( rewriting, 3, "Ok, the pre-unifier is: " << *preUnifier );
                }
                else
                    delete partition;
            }
        }
    }
    return APU;
}

void
XRewrite::createPartitionByPosition(
    const XAtom& queryAtom,
    const XAtom& ruleAtom,
    const XRule& rule,
    XPartition& outputPartition ) const
{
    assert_msg( queryAtom.getArity() == ruleAtom.getArity(), "Different arities" );
    trace_msg( rewriting, 4, "Create a partition by positions between " << queryAtom << " and " << ruleAtom );
    for( unsigned i=0; i<queryAtom.getTerms().size(); i++ )
    {
        const XTerm& queryTerm = queryAtom.getTerms().at(i);
        const XTerm& ruleTerm = ruleAtom.getTerms().at(i);

        assert_msg( queryTerm.getType() != XTerm::Null, "Null value" );
        assert_msg( ruleTerm.getType() != XTerm::Null, "Null value" );

        XTermType queryTermType;
        XTermType ruleTermType;
        if( queryTerm.getType() == XTerm::Variable )
            queryTermType = Variable;
        else
            queryTermType = Constant;
        if( ruleTerm.getType() == XTerm::Variable )
        {
            if( rule.isExistential(ruleTerm) )
                ruleTermType = ExistentialVariable;
            else if( rule.isFrontier(ruleTerm) )
                ruleTermType = FrontierVariable;
            else
                ruleTermType = Variable;
        }
        else
            ruleTermType = Constant;
        trace_msg( rewriting, 4, "Add an equivalence between " << queryTerm << " and " << ruleTerm );
        outputPartition.addEquivalence(queryTerm,queryTermType,ruleTerm,ruleTermType);
    }
}

vector< XPieceUnifier* >
XRewrite::SPUext(
    const XRule& query,
    const XRule& rule,
    const list< XPieceUnifier* >& APU,
    const XPieceUnifier* currentPreUnifier ) const
{
    trace_msg( rewriting, 3, "Extending unifier: " << *(currentPreUnifier) );
    vector< XPieceUnifier* > EPU;
    XPieceUnifier* tmpNonConstPointerToCurrentPreUnifier = const_cast< XPieceUnifier* >(currentPreUnifier);
    const unordered_set< XTerm >& stickyVariables = tmpNonConstPointerToCurrentPreUnifier->getStickyVariables();
    if( stickyVariables.size() == 0 )
    {
        trace_msg( rewriting, 3, "The set of its sticky variables is empty --> it is a single-piece unifier!!!" );
        // NOTICE: The destruction of the following unifier is delegated to the caller.
        XPieceUnifier* resultingUnifier = new XPieceUnifier(*currentPreUnifier);
        EPU.push_back(resultingUnifier);
    }
    else
    {
        trace_collection_msg( rewriting, 3, "The set of its sticky variables is", unordered_set< XTerm >, stickyVariables );
        // If one or more sticky variables are shared with the head, there is no possibilities to extend the current unifier
        // since the predicate of the query head is not included in any APU.
        bool isExtensible = true;
        const XHead* qHead = query.getHead();
        for( unsigned i=0; i<qHead->size(); i++ )
        {
            const XAtom& currentAtom = qHead->at(i);
            for( unsigned j=0; j<currentAtom.getTerms().size() && isExtensible; j++ )
            {
                if( stickyVariables.find(currentAtom.getTerms().at(j)) != stickyVariables.end() )
                    isExtensible = false;
            }
        }
        if( isExtensible )
        {
            // Compute idxAtomsCandidates, the set of atoms from the query which
            // are not in the sub-query and have at least one sticky variable.
            unordered_set< unsigned > idxAtomsCandidates;
            const unordered_set< unsigned >& subQueryAtomPositions = currentPreUnifier->getSubQueryAtomPositions();
            const XBody* qBody = query.getBody();
            for( unsigned i=0; i<qBody->size(); i++ )
            {
                // Consider the current atom only if it is not part of the current sub-query.
                if( subQueryAtomPositions.find(i) == subQueryAtomPositions.end() )
                {
                    const XAtom& currentAtom = qBody->at(i).getAtom();
                    bool ok = false;
                    for( unsigned j=0; j<currentAtom.getTerms().size() && !ok; j++ )
                    {
                        if( stickyVariables.find(currentAtom.getTerms().at(j)) != stickyVariables.end() )
                            ok = true;
                    }
                    if( ok )
                        idxAtomsCandidates.insert(i);
                }
            }
            assert_msg( idxAtomsCandidates.size() > 0, "If the current piece unifier is extensible at least one extending atom should exist." );
            trace_collection_msg( rewriting, 3, "Extending query atoms are in positions", unordered_set< unsigned >, idxAtomsCandidates );
            // NOTICE: The following call returns a vector of freshly instantiated unifiers; this function
            // is responsible for their deallocation. Since they won't be returned, they need to be
            // destroyed at the end of this block. They won't be returned because the elements which
            // will be returned are the ones given by the recursive call to SPUExt; the only exit condition
            // of this function allocates from scratch (copying the input one) the element to be returned.
            vector< XPieceUnifier* > Ext = Extend(currentPreUnifier,idxAtomsCandidates,APU);
            trace_msg( rewriting, 3, "Candidate extensions computed! Size: " << Ext.size() );
            for( unsigned i=0; i<Ext.size(); i++ )
            {
                trace_msg( rewriting, 3, "This is one of the returned candidate: " << *(Ext[i]) );
                vector< XPieceUnifier* > EPUExt = SPUext(query,rule,APU,Ext[i]);
                for( XPieceUnifier* unifierPointer: EPUExt )
                {
                    trace_msg( rewriting, 3, "The following is a single-piece unifier: " << *unifierPointer );
                    EPU.push_back(unifierPointer);
                }
                // This element won't be returned, thus it needs to be deallocated.
                delete Ext[i];
            }
        }
    }
    return EPU;
}

vector< XPieceUnifier* >
XRewrite::Extend(
    const XPieceUnifier* currentPreUnifier,
    unordered_set< unsigned > candidatesIdx,
    const list< XPieceUnifier* >& APU ) const
{
    vector< XPieceUnifier* > Ext;
    if( candidatesIdx.size() == 0 )
    {
        trace_msg( rewriting, 3, "Every extending atom was processed" );
        // NOTICE: The destruction of the following unifier is delegated to the caller.
        XPieceUnifier* resultingUnifier = new XPieceUnifier(*currentPreUnifier);
        Ext.push_back(resultingUnifier);
    }
    else
    {
        const XBody* queryBody = currentPreUnifier->getQuery().getBody();
        assert_msg( queryBody != NULL, "Null query" );
        const XAtom& a = queryBody->at(*candidatesIdx.begin()).getAtom();
        trace_msg( rewriting, 3, "Choose an extending atom: " << a );
//        bool hasAtLeastOneAPU = false;
        for( list< XPieceUnifier* >::const_iterator APUIt = APU.begin(); APUIt != APU.end(); APUIt++ )
        {
            XPieceUnifier* APUPtr = *APUIt;
            assert_msg( APUPtr != NULL, "Invalid unifier pointer" );
            // Every pre-unifier is composed by an atomic sub-query.
            assert_msg( APUPtr->getSubQuery().size() == 1, "Invalid pre-unifier sub-query" );
            if( APUPtr->getSubQuery().at(0) == a )
            {
                trace_msg( rewriting, 3, "An extending atomic pre unifier is " << *APUPtr );
                trace_msg( rewriting, 3, "Merge their partitions" );
//                hasAtLeastOneAPU = true;
                XPartition* partitionJoin = inputProgram.createPartition();
                partitionJoin->merge(currentPreUnifier->getPartition());
                partitionJoin->merge(APUPtr->getPartition());
                trace_msg( rewriting, 3, "The join between unifiers " << *currentPreUnifier << " and " << *APUPtr <<
                        " is given by: " << *partitionJoin );
                if( partitionJoin->isValid() )
                {
                    trace_msg( rewriting, 3, "The join is valid. Call the extending function recursively." );
                    // In this case, the destruction of partitionJoin is delegated to pieceUnifierJoin.
                    // The destruction of pieceUnifierJoin is done at the end of this block.
                    XPieceUnifier* pieceUnifierJoin = inputProgram.createPieceUnifier(
                            currentPreUnifier->getSubQuery(),
                            currentPreUnifier->getSubHead(),
                            partitionJoin,
                            currentPreUnifier->getQuery(),
                            currentPreUnifier->getRule(),
                            currentPreUnifier->getSubQueryAtomPositions());
                    pieceUnifierJoin->extendThisIsNotSinglePiece(APUPtr->getSubQuery(),APUPtr->getSubHead(),APUPtr->getSubQueryAtomPositions());

                    // That's why this set cannot be passed by reference. Recursive calls would modify
                    // the set and this may cause some problems since the following iterations
                    // might need the original version of the set.
                    candidatesIdx.erase(candidatesIdx.begin());

                    vector< XPieceUnifier* > extendedRecursively = Extend(pieceUnifierJoin,candidatesIdx,APU);
                    for( unsigned i=0; i<extendedRecursively.size(); i++ )
                    {
                        trace_msg( rewriting, 3, "Unifier " << *extendedRecursively[i] <<
                                " is a valid extension of " << *currentPreUnifier );
                        Ext.push_back(extendedRecursively[i]);
                    }
                    delete pieceUnifierJoin;
                }
                else
                {
                    trace_msg( rewriting, 3, "The join is not valid --> delete the partition just created." );
                    delete partitionJoin;
                }
            }
        }
//        traceIf( rewriting, 3, !hasAtLeastOneAPU, "Atom " << a << " does not have any APUs associated." );
    }
    return Ext;
}

/* The set of all single-piece aggregators of Q (the query) with R (the set of input TGDs) which is
 * obtained by aggregating the unifiers from all non-empty compatible subsets of SPU. For optimization
 * reasons, this set can be incrementally computed as follows:
 * 1) Let U1 = SPU = {u_1,...,u_k}, the u_i are called 1-unifiers.
 * 2) For i=2 to the greatest possible rank (i.e. until U_i is not empty); let U_i be the set of all
 * i-unifiers obtained by aggregating an (i-1)-unifier from U_(i-1) and a single-piece unifier from U_1
 * 3) Return the union of all the U_i obtained.
 */
void
XRewrite::computeSPUAggregators(
    vector< XPieceUnifier* >& SPU )
{
    auto sAggreTime = std::chrono::high_resolution_clock::now();
    trace_msg( rewriting, 2, "Aggregating single-piece unifiers from SPU" );
    size_t originalSPUSize = SPU.size();
    size_t oldSize = 0;
    size_t currentSize = SPU.size();
    // The first layer of aggregators is given by aggregating SPUs one another.
    // In order to avoid redundant aggregators, evaluate each SPU just with the ones which follow him.
    for( size_t i=0; i<originalSPUSize; i++ )
    {
        for( size_t j=i+1; j<originalSPUSize; j++ )
        {
            pair< XPieceUnifier*, bool > resAggregation = aggregatePieceUnifier(*SPU[i],*SPU[j]);
            if( resAggregation.second )
            {
                assert_msg( resAggregation.first != NULL, "Null aggregator" );
                SPU.push_back(resAggregation.first);
            }
        }
    }
    oldSize = currentSize;
    currentSize = SPU.size();
    // The i-th layer is given by aggregating each new aggregator derived during the (i-1)-th iteration with every starting SPUs.
    while( currentSize > oldSize )
    {
        for( size_t i=0; i<originalSPUSize; i++ )
        {
            for( size_t j=oldSize; j<currentSize; j++ )
            {
                pair< XPieceUnifier*, bool > resAggregation = aggregatePieceUnifier(*SPU[i],*SPU[j]);
                if( resAggregation.second )
                {
                    assert_msg( resAggregation.first != NULL, "Null aggregator" );
                    SPU.push_back(resAggregation.first);
                }
            }
        }

        oldSize = currentSize;
        currentSize = SPU.size();
    }
    trace_msg( rewriting, 2, "SPU aggregation complete!" );
    auto eAggrTime = std::chrono::high_resolution_clock::now();
    unifierAggregationDuration += ( eAggrTime - sAggreTime );
}

/* The aggregation between 2 or more single-piece aggregators is generated as follows:
 *
 * 1) check whether the input single-piece unifiers are *compatible*. This check has to be carried out
 * as follows:
 *
 * 1a) if their query subsets are disjoint, rename the input rule, R, of the second single-piece unifier
 * into R', in a way such that R and R' do not share any variables.
 * Rename the second single-piece unifiers according to such a renaming and generate the join of partitions;
 * if such a join is admissible (i.e. it does not contain an equivalence class with more than one constant),
 * then the single-piece unifiers are compatible. In this case, generate the aggregation of the input rule
 * (R ^ R', see the paper) and add it to the input program (at the end of this process, erase these rules
 * from the program).
 *
 * 2a) If the single-piece unifiers are compatible generate their single-piece aggregator, which is given
 * by merging their query subsets, their rule-head subsets (notice that the rule of the second single-piece
 * unifier was renamed within step 1) and their partitions (such a join was computed within step 1a).
 *
 * 2b) If the single-piece unifiers are not compatible, they cannot be aggregated.
 */
pair< XPieceUnifier*, bool >
XRewrite::aggregatePieceUnifier(
    const XPieceUnifier& piece1,
    const XPieceUnifier& piece2 )
{
    trace_msg( rewriting, 3, "Aggregating " << piece1 << " and " << piece2 );
    XPieceUnifier* aggregatedPieceUnifier = NULL;
    bool ok = false;
    if( piece1.isThisSubQueryDisjointWith(piece2) )
    {
        XMapping* renaming = renameInputRuleOf(piece2);
        // The destruction of such a partition is delegated to the piece unifier which stores it.
        XPartition* joinPartition = inputProgram.createPartition();
        joinPartition->merge(piece1.getPartition());
        joinPartition->mergePartitionToBeRenamed(piece2.getPartition(),*renaming);
        if( joinPartition->isValid() )
        {
            trace_msg( rewriting, 3, "Ok, they can be aggregated!" );
            XRule* aggregatedRule = createAggregatedRule(piece1.getRule(),piece2.getRule(),*renaming);
            XProgram::const_iterator itAggregatedRule = inputProgram.addTemporaryRule(*aggregatedRule);
            const XRule& aggregatedRuleRef = *itAggregatedRule;
            trace_msg( rewriting, 3, "The aggregated rule is " << *aggregatedRule );
            delete aggregatedRule;
            // Create the aggregated piece unifier.
            vector< XAtom > aggregatedSubQuery;
            for( unsigned i=0; i<piece1.getSubQuery().size(); i++ )
                aggregatedSubQuery.push_back(piece1.getSubQuery().at(i));
            for( unsigned i=0; i<piece2.getSubQuery().size(); i++ )
                aggregatedSubQuery.push_back(piece2.getSubQuery().at(i));

            vector< XAtom > aggregatedSubHead;
            for( unsigned i=0; i<piece1.getSubHead().size(); i++ )
                aggregatedSubHead.push_back(piece1.getSubHead().at(i));
            for( unsigned i=0; i<piece2.getSubHead().size(); i++ )
            {
                vector< XTerm > renamedTerms;
                for( unsigned j=0; j<piece2.getSubHead().at(i).getTerms().size(); j++ )
                {
                    XMapping::const_iterator itRenamedTerm = renaming->find(piece2.getSubHead().at(i).getTerms().at(j));
                    if( itRenamedTerm != renaming->end() )
                        renamedTerms.push_back(itRenamedTerm->second);
                    else
                        renamedTerms.push_back(piece2.getSubHead().at(i).getTerms().at(j));
                }
                XAtom* renamedHeadAtom = inputProgram.createAtom(piece2.getSubHead().at(i).getPredIndex(),renamedTerms);
                aggregatedSubHead.push_back(*renamedHeadAtom);
                delete renamedHeadAtom;
            }

            unordered_set< unsigned > aggregatedSubQueryAtomPos;
            aggregatedSubQueryAtomPos.insert(piece1.getSubQueryAtomPositions().begin(),piece1.getSubQueryAtomPositions().end());
            aggregatedSubQueryAtomPos.insert(piece2.getSubQueryAtomPositions().begin(),piece2.getSubQueryAtomPositions().end());
            aggregatedPieceUnifier = inputProgram.createPieceUnifier(
                    aggregatedSubQuery,
                    aggregatedSubHead,
                    joinPartition,
                    piece1.getQuery(),
                    aggregatedRuleRef,
                    aggregatedSubQueryAtomPos);

            trace_msg( rewriting, 3, "The aggregated piece-unifier is: " << *aggregatedPieceUnifier );
            ok = true;
        }
        else
            delete joinPartition;
        delete renaming;
    }
    traceIf( rewriting, 3, !ok, "Aggregation failed!" );
    return pair< XPieceUnifier*, bool >(aggregatedPieceUnifier,ok);
}

XMapping*
XRewrite::renameInputRuleOf(
    const XPieceUnifier& p )
{
    // The destruction of the renaming is delegated to the caller.
    XMapping* renaming = new XMapping();
    const XRule& ruleToBeRenamed = p.getRule();
    const XHead* head = ruleToBeRenamed.getHead();
    assert_msg( head != NULL, "Null head" );
    for( unsigned i=0; i<head->size(); i++ )
        for( unsigned j=0; j<head->at(i).getTerms().size(); j++ )
            if( head->at(i).getTerms().at(j).isStandardVar() )
            {
                XMapping::const_iterator it = renaming->find(head->at(i).getTerms().at(j));
                if( it == renaming->end() )
                {
                    stringstream ss;
                    inputProgram.incrementVariablesCounter();
                    ss << "X" << inputProgram.getVariablesCounter();
                    XTerm* renamedTerm = inputProgram.createStandardVariable(ss.str());
                    renaming->insert(pair< const XTerm&, const XTerm& >(head->at(i).getTerms().at(j),*renamedTerm));
                    delete renamedTerm;
                }
            }

    const XBody* body = ruleToBeRenamed.getBody();
    assert_msg( body != NULL, "Null body" );
    for( unsigned i=0; i<body->size(); i++ )
        for( unsigned j=0; j<body->at(i).getAtom().getTerms().size(); j++ )
            if( body->at(i).getAtom().getTerms().at(j).isStandardVar() )
            {
                XMapping::const_iterator it = renaming->find(body->at(i).getAtom().getTerms().at(j));
                if( it == renaming->end() )
                {
                    stringstream ss;
                    inputProgram.incrementVariablesCounter();
                    ss << "X" << inputProgram.getVariablesCounter();
                    XTerm* renamedTerm = inputProgram.createStandardVariable(ss.str());
                    renaming->insert(pair< const XTerm&, const XTerm& >(body->at(i).getAtom().getTerms().at(j),*renamedTerm));
                    delete renamedTerm;
                }
            }

    return renaming;
}

XRule*
XRewrite::createAggregatedRule(
    const XRule& ruleA,
    const XRule& ruleB,
    const XMapping& renaming ) const
{
    const XHead* headRuleA = ruleA.getHead();
    assert_msg( headRuleA != NULL, "Null head" );
    const XHead* headRuleB = ruleB.getHead();
    assert_msg( headRuleB != NULL, "Null head" );
    const XBody* bodyRuleA = ruleA.getBody();
    assert_msg( bodyRuleA != NULL, "Null body" );
    const XBody* bodyRuleB = ruleB.getBody();
    assert_msg( bodyRuleB != NULL, "Null body" );
    vector< XAtom > aggregatedHeadAtoms;
    for( unsigned i=0; i<headRuleA->size(); i++ )
        aggregatedHeadAtoms.push_back(headRuleA->at(i));
    for( unsigned i=0; i<headRuleB->size(); i++ )
    {
        vector< XTerm > renamedTerms;
        for( unsigned j=0; j<headRuleB->at(i).getTerms().size(); j++ )
        {
            XMapping::const_iterator it = renaming.find(headRuleB->at(i).getTerms().at(j));
            if( it != renaming.end() )
                renamedTerms.push_back(it->second);
            else
                renamedTerms.push_back(headRuleB->at(i).getTerms().at(j));
        }
        XAtom* renamedHeadAtom = inputProgram.createAtom(headRuleB->at(i).getPredIndex(),renamedTerms);
        aggregatedHeadAtoms.push_back(*renamedHeadAtom);
        delete renamedHeadAtom;
    }
    vector< XLiteral > aggregatedBodyLiterals;
    for( unsigned i=0; i<bodyRuleA->size(); i++ )
        aggregatedBodyLiterals.push_back(bodyRuleA->at(i));
    for( unsigned i=0; i<bodyRuleB->size(); i++ )
    {
        vector< XTerm > renamedTerms;
        for( unsigned j=0; j<bodyRuleB->at(i).getAtom().getTerms().size(); j++ )
        {
            XMapping::const_iterator it = renaming.find(bodyRuleB->at(i).getAtom().getTerms().at(j));
            if( it != renaming.end() )
                renamedTerms.push_back(it->second);
            else
                renamedTerms.push_back(bodyRuleB->at(i).getAtom().getTerms().at(j));
        }
        XAtom* renamedBodyAtom = inputProgram.createAtom(bodyRuleB->at(i).getAtom().getPredIndex(),renamedTerms);
        XLiteral* renamedBodyLiteral = inputProgram.createLiteral(*renamedBodyAtom,bodyRuleB->at(i).isNaf());
        aggregatedBodyLiterals.push_back(*renamedBodyLiteral);
        delete renamedBodyLiteral;
        delete renamedBodyAtom;
    }
    // The rule which is to be created has definitely a conjunctive head, because its head is given
    // by the aggregation of the heads of ruleA and ruleB respectively.
    XHead* aggregatedHead = inputProgram.createConjunctiveHead(aggregatedHeadAtoms);
    XBody* aggregatedBody = inputProgram.createBody(aggregatedBodyLiterals);
    // The destruction of aggregatedHead and aggregatedBody is delegated to aggregatedRule.
    XRule* aggregatedRule = inputProgram.createRule(aggregatedHead,aggregatedBody);
    // The destruction of aggregatedRule is delegated to the caller.
    return aggregatedRule;
}

XRule*
XRewrite::produceRewritingByPieceUnifier(
    XPieceUnifier& p )
{
    trace_msg( rewriting, 2, "Producing the rewriting rule for piece unifier: " << p );
    assert_msg( p.getQuery().getBody() != NULL, "Null body" );
    assert_msg( p.getRule().getBody() != NULL, "Null body" );
    assert_msg( p.getQuery().getHead() != NULL, "Null head" );
    assert_msg( p.getQuery().getHead()->isAtomic(), "Non-atomic query head" );
    XAtom* rewrittenHeadAtom;
    const XAtom& currentAtom = p.getQuery().getHead()->at(0);
    vector< XTerm > rewrittenTerms;
    for( unsigned j=0; j<currentAtom.getTerms().size(); j++ )
    {
        const XTerm& rewrittenTerm = p.getPartition().getMapping(currentAtom.getTerms().at(j));
        rewrittenTerms.push_back(rewrittenTerm);
    }
    rewrittenHeadAtom = inputProgram.createAtom(currentAtom.getPredIndex(),rewrittenTerms);
    XHead* rewrittenHead = inputProgram.createAtomicHead(*rewrittenHeadAtom);
    delete rewrittenHeadAtom;

    vector< XLiteral > rewrittenBodyAtoms;
    for( unsigned i=0; i<p.getQuery().getBody()->size(); i++ )
    {
        // Atoms which are in the subquery are replaced by the body of the rule.
        if( p.getSubQueryAtomPositions().find(i) == p.getSubQueryAtomPositions().end() )
        {
            const XAtom& currentAtom = p.getQuery().getBody()->at(i).getAtom();
            vector< XTerm > rewrittenTerms;
            for( unsigned j=0; j<currentAtom.getTerms().size(); j++ )
            {
                const XTerm& rewrittenTerm = p.getPartition().getMapping(currentAtom.getTerms().at(j));
                rewrittenTerms.push_back(rewrittenTerm);
            }
            XAtom* rewrittenAtom = inputProgram.createAtom(currentAtom.getPredIndex(),rewrittenTerms);
            XLiteral* rewrittenLiteral = inputProgram.createLiteral(*rewrittenAtom,p.getQuery().getBody()->at(i).isNaf());
            rewrittenBodyAtoms.push_back(*rewrittenLiteral);
            delete rewrittenLiteral;
            delete rewrittenAtom;
        }
    }
    for( unsigned i=0; i<p.getRule().getBody()->size(); i++ )
    {
        const XAtom& currentAtom = p.getRule().getBody()->at(i).getAtom();
        vector< XTerm > rewrittenTerms;
        for( unsigned j=0; j<currentAtom.getTerms().size(); j++ )
        {
            const XTerm& rewrittenTerm = p.getPartition().getMapping(currentAtom.getTerms().at(j));
            rewrittenTerms.push_back(rewrittenTerm);
        }
        XAtom* rewrittenAtom = inputProgram.createAtom(currentAtom.getPredIndex(),rewrittenTerms);
        XLiteral* rewrittenLiteral = inputProgram.createLiteral(*rewrittenAtom,p.getRule().getBody()->at(i).isNaf());
        rewrittenBodyAtoms.push_back(*rewrittenLiteral);
        delete rewrittenLiteral;
        delete rewrittenAtom;
    }
    XBody* rewrittenBody = inputProgram.createBody(rewrittenBodyAtoms);
    XRule* rewrittenRule = inputProgram.createRule(rewrittenHead,rewrittenBody);
    trace_msg( rewriting, 2, "The rule produced is: " << *rewrittenRule );
    return rewrittenRule;
}

bool
XRewrite::isUnnecessary(
    const XRule& rule )
{
    auto sUnnecessityTestTime = std::chrono::high_resolution_clock::now();
    trace_msg( rewriting, 2, "Check whether this rule is not necessary: " << rule );
    assert_msg( rule.getHead() != NULL, "Null head" );
    assert_msg( rule.getBody() != NULL, "Null body" );
    // First of all, the canonical renaming of the input rule has to be computed.
    // Thus, sort atoms from both head and body in a lexicographic way and, then,
    // rename variables in a canonical way starting from 1) the ones appearing in the
    // head, 2) the ones which are in join in the body and 3) all the other ones.
    vector< unsigned > orderedHeadPositions(rule.getHead()->size());
    vector< unsigned > orderedBodyPositions(rule.getBody()->size());
    for( unsigned i=0; i<orderedHeadPositions.size(); i++ )
        orderedHeadPositions[i] = i;
    for( unsigned i=0; i<orderedBodyPositions.size(); i++ )
        orderedBodyPositions[i] = i;
    mergeSort(*(rule.getHead()),orderedHeadPositions,0,orderedHeadPositions.size()-1);
    mergeSort(*(rule.getBody()),orderedBodyPositions,0,orderedBodyPositions.size()-1);

    unsigned varCounter = 0;
    XMapping renaming;

    // Canonical renaming procedure should start from the head of a rule.
    vector< XAtom > renamedHeadAtoms;
    for( unsigned i=0; i<orderedHeadPositions.size(); i++ )
    {
        assert_msg( orderedHeadPositions[i] < rule.getHead()->size(), "Index out of range" );
        const XAtom& currentAtom = rule.getHead()->at(orderedHeadPositions[i]);
        vector< XTerm > renamedTerms;
        for( unsigned j=0; j<currentAtom.getTerms().size(); j++ )
        {
            if( currentAtom.getTerms().at(j).isConst() )
            {
                renamedTerms.push_back(currentAtom.getTerms().at(j));
            }
            else
            {
                XMapping::const_iterator termIt = renaming.find(currentAtom.getTerms().at(j));
                if( termIt == renaming.end() )
                {
                    stringstream renamedTermStream;
                    // Character 'Z' has been never used before for variable names.
                    // This ensures the uniqueness of a canonical renaming.
                    renamedTermStream << "Z" << varCounter++;
                    XTerm* renamedTerm = inputProgram.createStandardVariable(renamedTermStream.str());
                    pair< XMapping::const_iterator, bool > res =
                            renaming.insert(pair< const XTerm&, const XTerm& >(currentAtom.getTerms().at(j),*renamedTerm));
                    termIt = res.first;
                    delete renamedTerm;
                }
                renamedTerms.push_back(termIt->second);
            }
        }
        XAtom* renamedHeadAtom = inputProgram.createAtom(currentAtom.getPredIndex(),renamedTerms,currentAtom.isTrueNegated());
        renamedHeadAtoms.push_back(*renamedHeadAtom);
        delete renamedHeadAtom;
    }
    vector< XLiteral > renamedBodyLiterals;
    for( unsigned i=0; i<orderedBodyPositions.size(); i++ )
    {
        assert_msg( orderedBodyPositions[i] < rule.getBody()->size(), "Index out of range" );
        const XLiteral& currentLiteral = rule.getBody()->at(orderedBodyPositions[i]);
        vector< XTerm > renamedTerms;
        for( unsigned j=0; j<currentLiteral.getTerms().size(); j++ )
        {
            if( currentLiteral.getTerms().at(j).isConst() )
            {
                renamedTerms.push_back(currentLiteral.getTerms().at(j));
            }
            else
            {
                XMapping::const_iterator termIt = renaming.find(currentLiteral.getTerms().at(j));
                if( termIt == renaming.end() )
                {
                    stringstream renamedTermStream;
                    // Character 'Z' has been never used before for variable names.
                    // This ensures the uniqueness of a canonical renaming.
                    renamedTermStream << "Z" << varCounter++;
                    XTerm* renamedTerm = inputProgram.createStandardVariable(renamedTermStream.str());
                    pair< XMapping::const_iterator, bool > res =
                            renaming.insert(pair< const XTerm&, const XTerm& >(currentLiteral.getTerms().at(j),*renamedTerm));
                    termIt = res.first;
                    delete renamedTerm;
                }
                renamedTerms.push_back(termIt->second);
            }
        }
        XAtom* renamedBodyAtom = inputProgram.createAtom(currentLiteral.getPredIndex(),renamedTerms,currentLiteral.getAtom().isTrueNegated());
        XLiteral* renamedBodyLiteral = inputProgram.createLiteral(*renamedBodyAtom,currentLiteral.isNaf());
        renamedBodyLiterals.push_back(*renamedBodyLiteral);
        delete renamedBodyLiteral;
        delete renamedBodyAtom;
    }

    // Sort out literals again.
    for( unsigned i=0; i<orderedHeadPositions.size(); i++ )
        orderedHeadPositions[i] = i;
    for( unsigned i=0; i<orderedBodyPositions.size(); i++ )
        orderedBodyPositions[i] = i;
    mergeSort(renamedHeadAtoms,orderedHeadPositions,0,orderedHeadPositions.size()-1);
    mergeSort(renamedBodyLiterals,orderedBodyPositions,0,orderedBodyPositions.size()-1);

    if( isInCanonicalRenamingCache(renamedHeadAtoms,orderedHeadPositions,renamedBodyLiterals,orderedBodyPositions) )
    {
        auto eUnnecessityTestTime = std::chrono::high_resolution_clock::now();
        queryNecessaryDuration += (eUnnecessityTestTime - sUnnecessityTestTime );
        return true;
    }
    auto eUnnecessityTestTime = std::chrono::high_resolution_clock::now();
    queryNecessaryDuration += (eUnnecessityTestTime - sUnnecessityTestTime );
    return false;
}

bool
XRewrite::isInCanonicalRenamingCache(
    const vector< XAtom >& headAtoms,
    const vector< unsigned > orderedHeadPositions,
    const vector< XLiteral >& bodyLiterals,
    const vector< unsigned > orderedBodyPositions )
{
    stringstream canonicalRenamingStream;
    for( unsigned i=0; i<orderedHeadPositions.size(); i++ )
    {
        assert_msg( orderedHeadPositions[i] < headAtoms.size(), "Index out of range" );
        const XAtom& currentAtom = headAtoms[orderedHeadPositions[i]];
        canonicalRenamingStream << currentAtom.getPredicateName();
        if( currentAtom.getTerms().size() > 0 )
            canonicalRenamingStream << "(";
        for( unsigned j=0; j<currentAtom.getTerms().size(); j++ )
        {
            canonicalRenamingStream << currentAtom.getTerms().at(j);
            if( j < currentAtom.getTerms().size()-1 )
                canonicalRenamingStream << ",";
        }
        if( currentAtom.getTerms().size() > 0 )
            canonicalRenamingStream << ")";
        if( i < orderedHeadPositions.size()-1 )
            canonicalRenamingStream << ",";
    }
    canonicalRenamingStream << ":-";
    for( unsigned i=0; i<orderedBodyPositions.size(); i++ )
    {
        assert_msg( orderedBodyPositions[i] < bodyLiterals.size(), "Index out of range" );
        const XLiteral& currentLiteral = bodyLiterals[orderedBodyPositions[i]];
        if( currentLiteral.isNaf() )
            canonicalRenamingStream << "not ";
        canonicalRenamingStream << currentLiteral.getPredicateName() << "(";
        for( unsigned j=0; j<currentLiteral.getTerms().size(); j++ )
        {
            canonicalRenamingStream << currentLiteral.getTerms().at(j);
            if( j < currentLiteral.getTerms().size()-1 )
                canonicalRenamingStream << ",";
        }
        canonicalRenamingStream << ")";
        if( i < orderedBodyPositions.size()-1 )
            canonicalRenamingStream << ",";
    }
    canonicalRenamingStream << ".";
    trace_msg( rewriting, 2, "The canonical rewriting of the current rule is: " << canonicalRenamingStream.str() );

    hash< string > strHash;
    size_t currentHash = strHash(canonicalRenamingStream.str());
    for( index_t i=0; i<canonicalRuleHashCodesCache.size(); i++ )
        if( currentHash == canonicalRuleHashCodesCache[i] )
            return true;

    canonicalRuleHashCodesCache.push_back(currentHash);
    return false;
}

XRule*
XRewrite::queryElimination(
    const XRule& query )
{
    auto sQueryEliminationTime = std::chrono::high_resolution_clock::now();
    trace_msg( rewriting, 2, "Query elimination:" );
    string reachabilityProblem(inputProgram.getPropagationGraphAsString());
    reachabilityProblem.append("reachable(X,Y,[X,Y],[L]):-edge(X,Y,L).\n");
    reachabilityProblem.append("reachable(X,Y,VL,EL):-reachable(X,Z,VL1,EL1),edge(Z,Y,LABEL),#insLast(VL1,Y,VL),#insLast(EL1,LABEL,EL),not #member(Y,VL1).\n");
    // For each body atom 'a', if there exists another body atom, 'b' (different from 'a'),
    // such that 'a' is covered by 'b', then 'a' is eliminated from the input query.
    const XBody* queryBody = query.getBody();
    assert_msg( queryBody != NULL, "Null query body" );
    set< unsigned > erasedAtomIndexSet;
    for( unsigned i=0; i<queryBody->size(); i++ )
    {
        if( erasedAtomIndexSet.find(i) == erasedAtomIndexSet.end() )
        {
            const XAtom& atom = queryBody->at(i).getAtom();

            bool covered = false;
            trace_msg( rewriting, 2, "Is " << atom << " eliminable?" );
            // Compute T(query,atom), i.e., the set of shared variables and constants from 'atom'.
            // Afterwards, locate the positions of such variables in the term list of the current atom.
            vector< unsigned > posTVars;
            for( unsigned t=0; t<atom.getTerms().size(); t++ )
            {
                if( atom.getTerms().at(t).isConst() )
                {
                    posTVars.push_back(t);
                }
                else if( atom.getTerms().at(t).isStandardVar() )
                {
                    if( query.getHeadOccurrences(atom.getTerms().at(t)) > 0 ||
                            query.getBodyOccurrences(atom.getTerms().at(t)) > 1 )
                    {
                        posTVars.push_back(t);
                    }
                }
            }
            trace_collection_msg( rewriting, 2, "These are the positions of the terms in T('query','atom') "
                    "(i.e., the set of shared variables and constants included in the current atom)",
                    vector< unsigned >, posTVars );
            for( unsigned j=0; j<queryBody->size() && !covered; j++ )
            {
                if( i != j && erasedAtomIndexSet.find(j) == erasedAtomIndexSet.end() )
                {
                    const XAtom& coveringCandidate = queryBody->at(j).getAtom();
                    // If T(query,atom) is a subset of terms(coveringCandidate) check
                    // whether coveringCandidate actually covers atom.
                    if( isSubset(atom.getTerms(),posTVars,coveringCandidate.getTerms()) )
                    {
                        trace_msg( rewriting, 2, "Check whether " << coveringCandidate << " is a covering atom of " << atom );
                        // If the atoms share the same predicate name and the variables from 'TVars' occur in 'coveringCandidate'
                        // in the same positions of 'atom', the coverage check is not needed.
                        bool coverageCheckNeeded = true;
                        // This check allows us to avoid nooses in the propagation graph.
                        if( atom.getPredicateName() == coveringCandidate.getPredicateName() )
                        {
                            bool varPositionsMatching = true;
                            for( unsigned p1=0; p1<posTVars.size(); p1++ )
                            {
                                assert_msg( posTVars[p1] < coveringCandidate.getTerms().size(), "Index out of range" );
                                if( atom.getTerms().at(posTVars[p1]) != coveringCandidate.getTerms().at(posTVars[p1]) )
                                    varPositionsMatching = false;
                            }
                            if( varPositionsMatching )
                            {
                                trace_msg( rewriting, 2, "Atom " << coveringCandidate << " covers "  << atom << " which has been erased." );
                                erasedAtomIndexSet.insert(i);
                                covered = true;
                                coverageCheckNeeded = false;
                            }
                        }
                        if( coverageCheckNeeded )
                        {
                            // If one of these atoms does not match any vertex in the propagation graph,
                            // this check will definitely be negative, thus avoid to execute it.
                            if( inputProgram.getPropagationGraph().getVertexId(atom.getPredIndex(),0).second &&
                                    inputProgram.getPropagationGraph().getVertexId(coveringCandidate.getPredIndex(),0).second )
                            {
                                // Check whether there exists a sequence S=sigma_(1)sigma_(2)...sigma_(m) for 'm'>=1 such that:
                                //
                                // 1) S is tight and compatible to coveringCandidate;
                                //
                                // 2) for each term 't' in T('query','atom') and for each position
                                //    of 'atom', 'p', where 't' appears there exists a minimal path 'p_(1)p_(2)...p_(m+1)'
                                //    in the propagation graph such that 'p_(1)' is in positions('coveringCandidate','t'),
                                //    'p_(m+1)'='p' and label('e_(j)','e_(j+1)')='sigma_(j)' for each 'j' in [m].
                                //
                                // This check is carried out by means of an invocation of DLV.
                                stringstream inputStream;
                                inputStream << reachabilityProblem;
                                stringstream finalQueryOnReachability;
                                finalQueryOnReachability << "ok(PATH):-";
                                for( unsigned p1=0; p1<posTVars.size(); p1++ )
                                {
                                    const XTerm& tVar = atom.getTerms().at(posTVars[p1]);
                                    assert_msg( inputProgram.getPropagationGraph().getVertexId(atom.getPredIndex(),posTVars[p1]).second,
                                            "The required vertex does not exist" );
                                    Vertex atomVertex = inputProgram.getPropagationGraph().getVertexId(atom.getPredIndex(),posTVars[p1]).first;
                                    for( unsigned p2=0; p2<query.getBodyPositions(tVar).size(); p2++ )
                                    {
                                        if( j == query.getBodyPositions(tVar).at(p2).atomPos )
                                        {
                                            assert_msg( inputProgram.getPropagationGraph().getVertexId(
                                                    coveringCandidate.getPredIndex(),query.getBodyPositions(tVar).at(p2).termPos).second,
                                                    "The required vertex does not exist" );
                                            Vertex coveringCandidateVertex = inputProgram.getPropagationGraph().getVertexId(
                                                    coveringCandidate.getPredIndex(),query.getBodyPositions(tVar).at(p2).termPos).first;
                                            inputStream << "reach(" << atomVertex << ",PATH):-"
                                                    << "reachable(" << coveringCandidateVertex << "," << atomVertex << ",_,PATH).\n";
                                        }
                                    }
                                    finalQueryOnReachability << "reach(" << atomVertex << ",PATH)";
                                    if( p1 < posTVars.size()-1 )
                                        finalQueryOnReachability << ",";
                                }
                                finalQueryOnReachability << "." << endl << "ok(PATH)?";
                                inputStream << finalQueryOnReachability.str();
                                trace_action( rewriting, 2,
                                        trace_tag( cerr, rewriting, 2 );
                                        cerr << "The input to DLV is the following:" << endl;
                                        char* tmpInputBuffer = new char[inputStream.str().length()+1];
                                        strcpy(tmpInputBuffer,inputStream.str().c_str());
                                        tmpInputBuffer[inputStream.str().length()] = '\0';
                                        char* t = NULL;
                                        t = strtok(tmpInputBuffer,"\n");
                                        while( t != NULL )
                                        {
                                            trace_tag( cerr, rewriting, 2 );
                                            cerr << "\t" << t << endl;
                                            t = strtok(NULL,"\n");
                                        }
                                        delete[] tmpInputBuffer;
                                    );
                                // DLV is called in order to solve the reachability problem.
                                char outputBuffer[BUFFER_MAX_LENGTH];
                                if( !isInReachabilityCache(inputStream.str(),outputBuffer) )
                                {
                                    auto sReachabilityTime = std::chrono::high_resolution_clock::now();
                                    Utils::systemCallTo("./executables/dlNofinitecheck",inputStream.str(),outputBuffer,BUFFER_MAX_LENGTH);
                                    auto eReachabilityTime = std::chrono::high_resolution_clock::now();
                                    reachabilityDuration += ( eReachabilityTime - sReachabilityTime );
                                    addToReachabilityCache(inputStream.str(),outputBuffer);
                                }
                                trace_action( rewriting, 2,
                                        trace_tag( cerr, rewriting, 2 );
                                        cerr << "The output from DLV is the following: ";
                                        if( strcmp(outputBuffer,"") == 0 )
                                            cerr << "EMPTY RESULT" << endl;
                                        else
                                        {
                                            cerr << std::endl;
                                            char* tmpOutputBuffer = new char[strlen(outputBuffer)+1];
                                            strcpy(tmpOutputBuffer,outputBuffer);
                                            tmpOutputBuffer[strlen(outputBuffer)] = '\0';
                                            char* t = NULL;
                                            t = strtok(tmpOutputBuffer,"\n");
                                            while( t != NULL )
                                            {
                                                trace_tag( cerr, rewriting, 2 );
                                                cerr << "\t" << t << endl;
                                                t = strtok(NULL,"\n");
                                            }
                                            delete[] tmpOutputBuffer;
                                        }
                                    );

                                // Each returned tuple represents a different path which proves the existence of
                                // a covering relationship between 'currentAtom' and 'coveringCandidate' only if such
                                // a path is compatible with 'coveringCandidate'. REMINDER: an atom 'a' is compatible
                                // with a sequence S of TGDs iff the body of the first TGD from S is homomorphic to 'a'.
                                trace_msg( rewriting, 3, "Analyzing the result..." << ( strcmp(outputBuffer,"") == 0 ? "EMPTY RESULT" : "" ) );
//                                bool validPath = false;
                                string text(outputBuffer);
                                boost::char_separator< char > sep("\n");
                                boost::tokenizer< boost::char_separator< char > > tokens(text,sep);
                                for( const auto& line : tokens )
                                {
                                    trace_msg( rewriting, 3, "The i^th path returned is: " << line );
                                    size_t delimiterIndex = line.find(',');
                                    if( delimiterIndex == string::npos )
                                        delimiterIndex = line.find(']');
                                    assert_msg( delimiterIndex != string::npos,
                                            "The sequence should either contain a ',' or be terminated by ']'" );

                                    int tgdIndex = -1;
                                    Utils::parseInteger(line.substr(1,delimiterIndex-1).c_str(),tgdIndex);
                                    assert_msg( (tgdIndex >= 0 && tgdIndex < (int)inputProgram.rulesSize()), "Index out of range" );
                                    XProgram::const_iterator tgdIterator = inputProgram.beginRules();
                                    advance(tgdIterator,tgdIndex);
                                    trace_msg( rewriting, 3, "The first TGD is rule number " << tgdIndex << ": " << *tgdIterator );
                                    // Check if the body of the first TGD is homomorphic to 'coveringCandidate'.
                                    assert_msg( tgdIterator->getBody() != NULL, "Null body" );
                                    assert_msg( tgdIterator->getBody()->size() > 0, "Invalid body size" );
                                    const XAtom& tgdListFirstAtom = tgdIterator->getBody()->at(0).getAtom();
                                    trace_msg( rewriting, 3, "Check whether the current sequence is compatible with 'coveringCandidate', i.e., "
                                            "whether " << tgdListFirstAtom << " is homomorphic to " << coveringCandidate );
                                    pair< bool, bool > resCache = homomorphismCache.inCache(
                                            pair< const XAtom&, const XAtom& >(coveringCandidate,tgdListFirstAtom));
                                    if( !resCache.first )
                                    {
                                        vector< XAtom > tgdAtomList;
                                        tgdAtomList.push_back(tgdListFirstAtom);
                                        vector< XAtom > coveringCandidateAtomList;
                                        coveringCandidateAtomList.push_back(coveringCandidate);
                                        auto sHomomorphismTime = std::chrono::high_resolution_clock::now();
                                        pair< XMapping*, bool  > resHomomorphism =
                                                isomorphismStrategy->isHomomorphicTo(coveringCandidateAtomList,tgdAtomList);
                                        auto eHomomorphismTime = std::chrono::high_resolution_clock::now();
                                        homomorphismDuration += ( eHomomorphismTime - sHomomorphismTime );
                                        if( resHomomorphism.second )
                                            delete resHomomorphism.first;
                                        homomorphismCache.cache(
                                            pair< const XAtom&, const XAtom& >(coveringCandidate,tgdListFirstAtom),
                                            resHomomorphism.second);
                                        resCache.second = resHomomorphism.second;
                                    }
                                    if( resCache.second )
                                    {
                                        // 'atom' is eliminable, because its covering set is not empty.
                                        trace_msg( rewriting, 2, "Atom " << coveringCandidate << " covers "  << atom << " which has been erased." );
                                        erasedAtomIndexSet.insert(i);
//                                        validPath = true;
                                        covered = true;
                                        break;
                                    }
                                }
                                traceIf( rewriting, 2, !covered, "Atom " << coveringCandidate << " does not cover "  << atom );
                            }
                            else
                            {
                                trace_msg( rewriting, 2, "Atom " << coveringCandidate << "does not cover" << atom );
                            }
                        }
                    }
                }
            }
            traceIf( rewriting, 2, !covered, "Atom " << atom << " is not covered." );
        }
    }
    XRule* rewrittenQuery = NULL;
    // If at least one atom has to be erased, create a new rule without the set of covered body atoms.
    if( erasedAtomIndexSet.size() > 0 )
    {
        assert_msg( ( query.getHead() != NULL && query.getHead()->isAtomic() ), "Not valid query head" );
        XHead* head = inputProgram.createAtomicHead(query.getHead()->at(0));
        vector< XLiteral > bodyLiterals;
        for( unsigned i=0; i<queryBody->size(); i++ )
        {
            if( erasedAtomIndexSet.find(i) == erasedAtomIndexSet.end() )
            {
                bodyLiterals.push_back(queryBody->at(i));
            }
        }
        XBody* body = inputProgram.createBody(bodyLiterals);
        rewrittenQuery = inputProgram.createRule(head,body);
    }
    auto eQueryEliminationTime = std::chrono::high_resolution_clock::now();
    queryEliminationDuration += ( eQueryEliminationTime - sQueryEliminationTime );
    return rewrittenQuery;
}

bool
XRewrite::isSubset(
    const vector< XTerm >& termList1,
    const vector< unsigned >& positionsToBeChecked,
    const vector< XTerm >& termList2 ) const
{
    bool ok = true;
    for( unsigned t1=0; t1<positionsToBeChecked.size() && ok; t1++ )
    {
        bool found = false;
        for( unsigned t2=0; t2<termList2.size() && !found; t2++ )
        {
            assert_msg( positionsToBeChecked[t1] < termList1.size(), "Index out of range" );
            if( termList1[positionsToBeChecked[t1]] == termList2[t2] )
                found = true;
        }
        if( !found )
            ok = false;
    }
    return ok;
}

bool
XRewrite::isInReachabilityCache(
    const string& input,
    char output[] ) const
{
    hash< string > strHash;
    size_t inputHash = strHash(input);
    unordered_map< size_t, string >::const_iterator it = reachabilityCache.find(inputHash);
    if( it != reachabilityCache.end() )
    {
        trace_msg( rewriting, 2, "Retrieving from cache" );
        strcpy(output,it->second.c_str());
        return true;
    }
    return false;
}

void
XRewrite::addToReachabilityCache(
    const string& input,
    char output[] )
{
    hash< string > strHash;
    size_t inputHash = strHash(input);
    reachabilityCache.insert(pair< const size_t&, const string& >(inputHash,string(output)));
}

void
XRewrite::eraseQueryWithAuxPreds(
    vector< XRule* > queryRules,
    vector< XRule* >& outputQueryRules ) const
{
    for( index_t i=0; i<queryRules.size(); i++ )
    {
        const XBody* ruleBody = queryRules[i]->getBody();
        assert_msg( ruleBody != NULL, "Null body!" );
        bool hasAux = false;
        for( unsigned j=0; j<ruleBody->size() && !hasAux; j++ )
        {
            if( boost::starts_with(ruleBody->at(j).getPredicateName(),"aux_") )
                hasAux = true;
        }
        if( hasAux )
            delete queryRules[i];
        else
            outputQueryRules.push_back(queryRules[i]);
    }
}
