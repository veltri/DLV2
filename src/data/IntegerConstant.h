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
 * File:   IntegerConstant.h
 * Author: cesco
 *
 * Created on 28 febbraio 2014, 16.17
 */

#ifndef INTEGERCONSTANT_H
#define	INTEGERCONSTANT_H

#include <sstream>
#include "Term.h"
#include "Atom.h"

class IntegerConstant : public Term {
public:
    IntegerConstant( int i );
    IntegerConstant( const IntegerConstant& i );
    ~IntegerConstant() { }
    
    Type getType() { return Term::Integer; }
    string toString() const;
        
private:
    friend inline ostream& operator<< ( ostream&, const IntegerConstant& );
};

inline ostream& operator<< ( ostream& out, const IntegerConstant& c )
{
    out << c.toString();
    return out;
}

#endif	/* INTEGERCONSTANT_H */

