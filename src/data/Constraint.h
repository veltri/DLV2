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
 * File:   Constraint.h
 * Author: cesco
 *
 * Created on 25 marzo 2014, 13.54
 */

#ifndef CONSTRAINT_H
#define	CONSTRAINT_H

#include <vector>
#include "Literal.h"

class Constraint {
public:
    Constraint( vector<Literal> b ): body(b) { } 
    Constraint( const Constraint& c ): body(c.body) { }
    ~Constraint() { }
    
    void addToBody( const Literal& l ) { body.push_back(l); }
    
private:
    friend inline ostream& operator<< ( ostream&, const Constraint& );
    
    vector<Literal> body;
};

ostream& 
operator<< ( 
    ostream& out,
    const Constraint& c )
{
    out << ":- ";
    for( unsigned i=0; i<c.body.size(); i++ )
    {
        out << c.body[i];
        if( i<c.body.size()-1 )
            out << ", ";
    }
    out << ".";
    
    return out;
}

#endif	/* CONSTRAINT_H */

