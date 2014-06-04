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
 * File:   SimpleInputBuilder.h
 * Author: cesco
 *
 * Created on 7 marzo 2014, 10.53
 */

#ifndef SIMPLEINPUTBUILDER_H
#define	SIMPLEINPUTBUILDER_H

#include "../mockdata/Program.h"
#include "../mockdata/AggregateElement.h"
#include "InputBuilder.h"
#include <vector>

namespace DLV2
{

    class SimpleInputBuilder : public InputBuilder {
    public:
        SimpleInputBuilder();
        virtual ~SimpleInputBuilder();

        virtual void onDirective( char* directiveName, char* directiveValue );
        virtual void onRule();
        virtual void onConstraint();
        virtual void onWeakConstraint();
        virtual void onQuery();
        virtual void onHeadAtom();
        virtual void onHead() { }
        virtual void onBodyLiteral();
        virtual void onBody() { }
        virtual void onNafLiteral( bool naf = false );
        virtual void onAtom( bool isStrongNeg = false );
        virtual void onExistentialAtom();
        virtual void onPredicateName( char* );
        virtual void onExistentialVariable( char* );
        virtual void onEqualOperator();
        virtual void onUnequalOperator();
        virtual void onLessOperator();
        virtual void onLessOrEqualOperator();
        virtual void onGreaterOperator();
        virtual void onGreaterOrEqualOperator();
        virtual void onTerm( char* );
        virtual void onTerm( int );
        virtual void onUnknownVariable();
        virtual void onFunction( char*, int );
        virtual void onTermDash();
        virtual void onTermParams();
        virtual void onTermRange( char*, char* );
        virtual void onArithmeticOperation( char );
        virtual void onWeightAtLevels( int, int, int );
        virtual void onChoiceLowerGuard();
        virtual void onChoiceUpperGuard();
        virtual void onChoiceElementAtom();
        virtual void onChoiceElementLiteral();
        virtual void onChoiceElement();
        virtual void onChoiceAtom();
        virtual void onBuiltinAtom();
        virtual void onAggregateLowerGuard();
        virtual void onAggregateUpperGuard();
        virtual void onAggregateFunction( char* );
        virtual void onAggregateGroundTerm( char*, bool dash = false );
        virtual void onAggregateVariableTerm( char* );
        virtual void onAggregateUnknownVariable();
        virtual void onAggregateNafLiteral();
        virtual void onAggregateElement();
        virtual void onAggregate( bool naf = false );
        // Not derived methods
        Program& getProgram();
        Atom* getQuery();
        void newTerm( char*, std::vector<Term>&, bool dash = false ); 

        bool isNumeric( const char*, int );

    private:
        Program* program;
        std::vector<Atom> head;
        std::vector<Literal> body;
        Literal* currentLiteral;
        Atom* currentAtom;
        std::string predName;
        std::vector<Term> termStack; 
        std::vector<Term> existVars;
        struct VariableIndex {
            std::string varName;
            unsigned varIndex;
        };
        std::vector<VariableIndex> localVariables; 
        unsigned varCounter;
        Atom* query;
        unsigned nTermsForWeight; 
        unsigned nTermsForLevel;
        unsigned nTermsAfterLevel;
        Term* lowerGuard;
        Term* upperGuard;
        std::string binop;
        std::string lowerBinop;
        std::string upperBinop;
        ChoiceElement* currentChoiceElement;
        std::vector<ChoiceElement> choiceElements;
        ChoiceAtom* currentChoiceAtom;
        std::string aggregateFunction;
        std::vector<Term> aggregateElementTerms;
        std::vector<Literal> aggregateElementLiterals;
        std::vector<AggregateElement> aggregateElements;
    };

};
#endif	/* SIMPLEINPUTBUILDER_H */

