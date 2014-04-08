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
 * File:   Variable.h
 * Author: cesco
 *
 * Created on 28 febbraio 2014, 13.16
 */

#ifndef VARIABLE_H
#define	VARIABLE_H

#include <sstream>
#include "Term.h"

class Variable : public Term {
public:
    Variable( unsigned i, string v ): Term(i), value(v) { }
    Variable( const Variable& v ): Term(v.index), value(v.value) { }
    ~Variable() { }

    Type getType() { return Term::Variable; }
    string toString() const { return value; }
    
private:
    friend inline ostream& operator<< ( ostream& out, const Variable& v );
    string value;
};

inline ostream& operator<< ( ostream& out, const Variable& v )
{
    out << v.toString();
    return out;
}

#endif	/* VARIABLE_H */