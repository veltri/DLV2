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
 * File:   Term.h
 * Author: cesco
 *
 * Created on 28 febbraio 2014, 11.29
 */

#ifndef TERM_H
#define TERM_H

#include <iostream>

using namespace std;

class Term {
public:
    enum Type{ Variable, Integer, String };
    
    Term( unsigned i ): index(i) { }
    Term( const Term& t ): index(t.index) { }
    virtual ~Term() { }
    
    virtual Type getType() = 0;
    virtual string toString() const = 0;
    
    unsigned getIndex() { return index; }
    
protected:
    unsigned index;

};

#endif	/* TERM_H */

