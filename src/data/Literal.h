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
#include "AggregateElement.h"

using namespace std;

class AggregateElement;
inline ostream& operator<< ( ostream&, const AggregateElement& );

class Literal {
public:
    // Classic literal constructor
    Literal( const Atom& a, bool neg );
    // Aggregate constructor
    Literal( Term*, string, Term*, string, string, vector<AggregateElement>, bool );
    // Copy constructor
    Literal( const Literal& l );
    ~Literal();
    
    void setIsNaf( bool isNaf ) { isNegative = isNaf; }
    
private:
    friend inline ostream& operator<< ( ostream&, const Literal& );
    
    Atom* atom;
    bool isNegative;
    
    bool isAggregate;
    Term* lowerGuard;
    string lowerBinop;
    Term* upperGuard;
    string upperBinop;
    string aggregateFunction;
    vector<AggregateElement> aggregateElements;
};

ostream& 
operator<< ( 
    ostream& out, 
    const Literal& l )
{
    if( l.isNegative )
            out << "not ";
    if( l.isAggregate )
    {
        assert_msg( (l.lowerGuard != NULL || l.upperGuard != NULL),
            "Invalid aggregate literal, null guards");
        if( l.lowerGuard )
            out << *(l.lowerGuard) << l.lowerBinop;
        out << l.aggregateFunction << "{";
        for( unsigned i=0; i<l.aggregateElements.size(); i++ )
        {
            out << l.aggregateElements[i];
            if( i < l.aggregateElements.size()-1 )
                out << ";";
        }
        out << "}";
        if( l.upperGuard )
            out << l.upperBinop << *(l.upperGuard);
    }
    else
    {
        assert_msg( l.atom != NULL, "Invalid literal: null atom!");
        out << *(l.atom);
    }
    return out;
}

#endif	/* LITERAL_H */

