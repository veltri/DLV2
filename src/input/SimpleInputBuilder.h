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

#include "InputBuilder.h"
#include <vector>

class SimpleInputBuilder : public InputBuilder {
public:
    SimpleInputBuilder();
    ~SimpleInputBuilder();
    
    virtual void onRule();
    virtual void onConstraint();
    virtual void onWeakConstraint();
    virtual void onQuery();
    virtual void addToHead();
    virtual void addToBody();
    virtual void onNafLiteral( bool naf = false );
    virtual void onAtom( bool isStrongNeg = false );
    virtual void onExistentialAtom();
    virtual void predicateName( char* );
    virtual void onExistentialVariable( char* );
    virtual void onTerm( char* );
    virtual void onTerm( int );
    virtual void onFunction( char*, int );
    virtual void onTermDash( int );
    virtual void onTermParams( int );
    virtual void onArithmeticOperation( char );
    virtual void onWeight( int );
    virtual void onLevel( int );
    virtual void onLevelsAndTerms( int, int );
    // Not derived methods
    Program& getProgram();
    Atom* getQuery();
      
    bool isNumeric( const char*, int );
    
private:   
    Program* program;
    vector<Atom> head;
    vector<Literal> body;
    Rule* currentRule;
    Literal* currentLiteral;
    Atom* currentAtom;
    string predName;
    Term* currentTerm;
    vector<Term*> termStack; 
    vector<Term*> allTerms;
    vector<Variable> existVars;
    struct VariableIndex {
        string varName;
        unsigned varIndex;
    };
    vector<VariableIndex> localVariables; 
    unsigned varCounter;
    Atom* query;
};

#endif	/* SIMPLEINPUTBUILDER_H */

