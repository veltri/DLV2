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
 * File:   XRewrite.h
 * Author: pierfrancesco
 *
 * Created on 03 dicembre 2014, 13.44
 */

#ifndef XREWRITE_H
#define XREWRITE_H

#include "RewritingAlgorithm.h"

#include "../data/XHomomorphismCache.h"

#include <vector>
#include <list>
#include <chrono>

namespace DLV2{ namespace REWRITERS{

    class IsomorphismCheckStrategy;

    class XRewrite: public RewritingAlgorithm {
    public:
        XRewrite( XProgram& input );
        virtual ~XRewrite();

        virtual std::vector< XRule* > rewrite();
        virtual void printStatistics() const;

    protected:
        void pushRewriting( XRule* rewriting, std::vector< XRule* >& rewritings );
        void encodeInputQueries( std::vector< XRule* >& finalRewriting );
        // Algorithm 3 of the paper
        std::vector< XPieceUnifier* > computeSPU( const XRule& query, const XRule& rule ) const;
        // Algorithm 2 of the paper
        std::list< XPieceUnifier* > computeAPU( const XRule& query, const XRule& rule ) const;
        void createPartitionByPosition(
                const XAtom& queryAtom,
                const XAtom& ruleAtom,
                const XRule& rule,
                XPartition& outputPartition ) const;
        // Algorithm 4 of the paper
        std::vector< XPieceUnifier* > SPUext(
                const XRule& query,
                const XRule& rule,
                const std::list< XPieceUnifier* >& APU,
                const XPieceUnifier* currentPreUnifier ) const;
        // Algorithm 5 of the paper
        std::vector< XPieceUnifier* > Extend(
                const XPieceUnifier* currentPreUnifier,
                std::unordered_set< unsigned > candidates,
                const std::list< XPieceUnifier* >& APU ) const;
        void computeSPUAggregators( std::vector< XPieceUnifier* >& SPU );
        std::pair< XPieceUnifier*, bool > aggregatePieceUnifier( const XPieceUnifier& piece1, const XPieceUnifier& piece2 );
        XMapping* renameInputRuleOf( const XPieceUnifier& p );
        XRule* createAggregatedRule( const XRule& ruleA, const XRule& ruleB, const XMapping& renaming ) const;
        XRule* produceRewritingByPieceUnifier( XPieceUnifier& p );
        bool isUnnecessary( const XRule& rule );
        bool isInCanonicalRenamingCache(
                const std::vector< XAtom >& headAtoms,
                const std::vector< unsigned > orderedHeadPositions,
                const std::vector< XLiteral >& bodyLiterals,
                const std::vector< unsigned > orderedBodyPositions );
        XRule* queryElimination( const XRule& query );
        bool isSubset(
                const std::vector< XTerm >& termList1,
                const std::vector< unsigned >& positionsToBeChecked,
                const std::vector< XTerm >& termList2 ) const;
        bool isInReachabilityCache( const std::string& input, char output[] ) const;
        void addToReachabilityCache( const std::string& input, char output[] );

        template < typename T >
        void mergeSort(
                const T& vectorToBeSorted,
                std::vector< unsigned >& orderedPositions,
                unsigned left,
                unsigned right ) const;

        template < typename T >
        void merge(
                const T& vectorToBeSorted,
                std::vector< unsigned >& orderedPositions,
                unsigned left,
                unsigned center,
                unsigned right ) const;


        unsigned numberOfAggregatedRulesAddedToTheProgram;
        IsomorphismCheckStrategy* isomorphismStrategy;
        // This vector stores hash_codes of the canonical renaming of the rewriting rules.
        std::vector< size_t > canonicalRuleHashCodesCache;
        // This map stores (possibly empty) paths between two nodes in the propagation graph.
        // Notice that, keys are hash codes of strings representing input to DLV for the particular instance of the reachability problem.
        std::unordered_map< size_t, std::string > reachabilityCache;
        // Given the hash codes of two atoms, a1 and a2, this map says whether a1 is homomorphich to a2.
        XHomomorphismCache homomorphismCache;
        // Notice that, our algorithm is designed to work with BCQs. Anyway, this is not a restriction
        // since we can actually process a CQ with free variables x_1,...,x_q by translating
        // it into a BCQ with an added atom QUERY_ANS(x_1,...,x_q), where QUERY_ANS is a special predicate
        // not occurring anywhere else. Of course, we need to transform the final result by removing this
        // atom from the body in order to produce a rewriting which can be processed by a Datalog engine.
        // This variable stores the predicate index of the atom which will be moved from the head to the body
        // If the head of the input query is already propositional (BCQs), no atoms will be moved to the body
        // and this index won't be modified.
        index_t predicateNewQueryHeadAtom;
        index_t predicateOldQueryHeadAtom;

        // Statistics
        std::chrono::duration< double, std::milli > rewritingDuration;
        size_t rewritingSize;
        std::chrono::duration< double, std::milli > unifierAggregationDuration;
        std::chrono::duration< double, std::milli > queryNecessaryDuration;
        std::chrono::duration< double, std::milli > queryEliminationDuration;
        std::chrono::duration< double, std::milli > reachabilityDuration;
        std::chrono::duration< double, std::milli > homomorphismDuration;

    };


    template < typename T >
    void
    XRewrite::mergeSort(
        const T& vectorToBeSorted,
        std::vector< unsigned >& orderedPositions,
        unsigned left,
        unsigned right ) const
    {
        if( left < right )
        {
            unsigned center = (left+right)/2;
            mergeSort(vectorToBeSorted,orderedPositions,left,center);
            mergeSort(vectorToBeSorted,orderedPositions,center+1,right);
            merge(vectorToBeSorted,orderedPositions,left,center,right);
        }
    }

    template < typename T >
    void
    XRewrite::merge(
        const T& vectorToBeSorted,
        std::vector< unsigned >& orderedPositions,
        unsigned left,
        unsigned center,
        unsigned right ) const
    {
        unsigned i=left;
        unsigned j=center+1;
        unsigned k=left;
        std::vector< unsigned > tmp(right-left+1);
        while( i <= center && j <= right )
        {
            if( vectorToBeSorted[orderedPositions[i]] <= vectorToBeSorted[orderedPositions[j]] )
                tmp[k-left] = orderedPositions[i++];
            else
                tmp[k-left] = orderedPositions[j++];
            k++;
        }
        while( i <= center )
        {
            tmp[k-left] = orderedPositions[i++];
            k++;
        }
        while( j <= right )
        {
            tmp[k-left] = orderedPositions[j++];
            k++;
        }
        for( unsigned x=left; x<right+1; x++ )
            orderedPositions[x] = tmp[x-left];
    }

};};

#endif /* XREWRITE_H */
