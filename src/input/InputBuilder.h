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
 * File:   InputBuilder.h
 * Author: cesco
 *
 * Created on 6 marzo 2014, 23.03
 */

#ifndef INPUTBUILDER_H
#define	INPUTBUILDER_H

#include "../data/Program.h"

class InputBuilder {
public:
    InputBuilder() { }
    ~InputBuilder() { }
    
    virtual void onRule() = 0;
    virtual void onConstraint() = 0;
    virtual void onWeakConstraint() = 0;
    virtual void onQuery() = 0;
    virtual void addToHead() = 0;
    virtual void addToBody() = 0;
    virtual void onNafLiteral( bool naf = false ) = 0;
    virtual void onAtom( bool isStrongNeg = false ) = 0;
    virtual void onExistentialAtom() = 0;
    virtual void predicateName( char* ) = 0;
    virtual void onExistentialVariable( char* ) = 0;
    virtual void onTerm( char* ) = 0;
    virtual void onTerm( int ) = 0;
    virtual void onFunction( char*, int ) = 0;
    virtual void onTermDash() = 0;
    virtual void onTermParams() = 0;
    virtual void onArithmeticOperation( char ) = 0;
    virtual void onWeightAtLevels( int, int, int ) = 0;
    
};

#endif	/* INPUTBUILDER_H */

