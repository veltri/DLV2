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
 * File:   DepGraphBuilder.h
 * Author: cesco
 *
 * Created on 19 maggio 2014, 12.07
 */

#ifndef DEPGRAPHBUILDER_H
#define	DEPGRAPHBUILDER_H

#include "InputBuilder.h"
#include "../depgraph/LabeledDependencyGraph.h"
#include <vector>
#include <string>

namespace DLV2
{
    
    class DepGraphBuilder: public InputBuilder {
    public:
        
        DepGraphBuilder(): isNaf(false), isBuiltin(false), isChoice(false), aggregateLiteralPlaceholder(0) { }
        virtual ~DepGraphBuilder() { }

        virtual void onDirective( char* directiveName, char* directiveValue );
        virtual void onRule();
        virtual void onConstraint();
        virtual void onWeakConstraint();
        virtual void onQuery();
        virtual void onHeadAtom();
        virtual void onHead();
        virtual void onBodyLiteral();
        virtual void onBody();
        virtual void onNafLiteral( bool naf = false );
        virtual void onAtom( bool isStrongNeg = false );
        virtual void onExistentialAtom();
        virtual void onPredicateName( char* name );
        virtual void onExistentialVariable( char* var );
        virtual void onEqualOperator();
        virtual void onUnequalOperator();
        virtual void onLessOperator();
        virtual void onLessOrEqualOperator();
        virtual void onGreaterOperator();
        virtual void onGreaterOrEqualOperator();
        virtual void onTerm( char* value );
        virtual void onTerm( int value );
        virtual void onUnknownVariable();
        virtual void onFunction( char* functionSymbol, int nTerms );
        virtual void onTermDash();
        virtual void onTermParams();
        virtual void onTermRange( char* lowerBound, char* upperBound );
        virtual void onArithmeticOperation( char arithOperator );
        virtual void onWeightAtLevels( int nWeight, int nLevel, int nTerm );
        virtual void onChoiceLowerGuard();
        virtual void onChoiceUpperGuard();
        virtual void onChoiceElementAtom();
        virtual void onChoiceElementLiteral();
        virtual void onChoiceElement();
        virtual void onChoiceAtom();
        virtual void onBuiltinAtom();
        virtual void onAggregateLowerGuard();
        virtual void onAggregateUpperGuard();
        virtual void onAggregateFunction( char* functionSymbol );
        virtual void onAggregateGroundTerm( char* value, bool dash = false );
        virtual void onAggregateVariableTerm( char* value );
        virtual void onAggregateUnknownVariable();
        virtual void onAggregateNafLiteral();
        virtual void onAggregateElement();
        virtual void onAggregate( bool naf = false );
        // Not derived methods
        LabeledDependencyGraph<>& getLabeledDependencyGraph() { return graph; }
        
    private:
        
        typedef std::pair<std::string,bool> DepGraphLiteral;
        
        std::vector<std::string> atomStack;
        std::vector<DepGraphLiteral> literalStack;
        std::string predName;
        bool isNaf;
        bool isBuiltin;
        bool isChoice;
        std::string aggregateFunction;
        std::string aggregateSet;
        std::vector<std::string> currentAggregateElementTerms;
        std::vector<DepGraphLiteral> aggregateLiteralStack;
        unsigned aggregateLiteralPlaceholder;
        std::string currentChoiceElementAtom;
        std::vector<DepGraphLiteral> currentChoiceElementLiterals;
        LabeledDependencyGraph<> graph;
    };
    
};

#endif	/* DEPGRAPHBUILDER_H */

