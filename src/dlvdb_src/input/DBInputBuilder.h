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
 * File:   DBInputBuilder.h
 * Author: pierfrancesco
 *
 * Created on 10 agosto 2014, 19.46
 */

#ifndef DBINPUTBUILDER_H
#define	DBINPUTBUILDER_H

#include "../data/DBProgram.h"
#include "../../input/InputBuilder.h"
#include "../../util/DBConnection.h"
#include <sstream>

namespace DLV2{ namespace DB{
    
    class DBInputBuilder: public InputBuilder {
    public:
        DBInputBuilder( DBConnection& con );
        virtual ~DBInputBuilder();

        virtual void onDirective( char* directiveName, char* directiveValue ) { }
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
        
        void newTerm( char*, std::vector< DBTerm* >&, bool dash = false );
        static bool isNumeric( const char*, int );
        
        DBProgram* getProgram() { return program; }
        DBAtom* getQuery() { return query; }
            
    private:
        
        DBProgram* program;
        QueryBuilder* queryBuilder;
        
        std::vector< DBTerm* > termStack;
        std::string predName;
        DBAtom* currentAtom;
        bool isChoice;
        DBLiteral* currentLiteral;
        std::vector< DBAtom* > head;
        std::vector< DBLiteral* > body;
        DBAtom* query;
        unsigned nTermsForWeight;
        unsigned nTermsForLevel;
        unsigned nTermsAfterLevel;
        std::string binop;
        std::string lowerBinop;
        std::string upperBinop;
        DBTerm* lowerGuard;
        DBTerm* upperGuard;
        std::string aggregateFunction;
        std::vector< DBTerm* > aggregateElementTerms;
        std::vector< DBLiteral* > aggregateElementLiterals;
        std::vector< DBAggregateElement* > aggregateElements;
        std::stringstream aggregateLabel;
        bool hasNegation;
        bool hasAggregates;
        bool hasBuiltins;
        bool hasDisjunction;
    };

};};


#endif	/* DBINPUTBUILDER_H */

