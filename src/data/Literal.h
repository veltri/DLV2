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
 * File:   Literal.h
 * Author: pierfrancesco
 *
 * Created on 28 febbraio 2014, 13.00
 */

#ifndef LITERAL_H
#define	LITERAL_H

#include <iostream>
#include "Atom.h"

using namespace std;

class Literal {
public:
    Literal( Atom a, bool neg ): atom(a), isNegative(neg) { }
    Literal( const Literal& l ): atom(l.atom), isNegative(l.isNegative) { }
    ~Literal() { }
    
    void setIsNaf( bool isNaf ) { isNegative = isNaf; }
    
private:
    friend inline ostream& operator<< ( ostream&, const Literal& );
    
    Atom atom;
    bool isNegative;
};

ostream& 
operator<< ( 
    ostream& out, 
    const Literal& l )
{
    if( l.isNegative )
        out << "not ";
    out << l.atom;
    return out;
}

#endif	/* LITERAL_H */

