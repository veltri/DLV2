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
 * File:   StringConstant.h
 * Author: cesco
 *
 * Created on 28 febbraio 2014, 16.12
 */

#ifndef STRINGCONSTANT_H
#define	STRINGCONSTANT_H

#include "Atom.h"
#include <string>

using namespace std;

class StringConstant : public Term {
public:
    StringConstant( string n ): Term(Atom::addStringConstant(n)) { }
    StringConstant( const StringConstant& s ): Term(s.index) { }
    ~StringConstant() { }
    
    Type getType() { return Term::String; }
    string toString() const { return Atom::getStringConstant(index); }

private:
    friend inline ostream& operator<< ( ostream&, const StringConstant& );
};

inline ostream& operator<< ( ostream& out, const StringConstant& s )
{
    out << s.toString();
    return out;
}

#endif	/* STRINGCONSTANT_H */

