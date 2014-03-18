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
 * File:   Atom.h
 * Author: pierfrancesco
 *
 * Created on 28 febbraio 2014, 13.02
 */

#ifndef ATOM_H
#define	ATOM_H

#include <string>
#include <vector>
#include "Term.h"

using namespace std;

class Atom {
public:
    Atom( string, unsigned, vector<Term*>, bool tNeg = false );
    Atom( const Atom& a );
    ~Atom() { }
    
    static unsigned addPredicateName( string, unsigned );
    static string getPredicateName( unsigned );
    static unsigned getPredicateArity( unsigned );
    static unsigned addStringConstant( string );
    static string getStringConstant( unsigned );
    static unsigned addIntegerConstant( int );
    static int getIntegerConstant( unsigned );
    
    string getPredName() const { return Atom::getPredicateName(predIndex); }
    unsigned getIndex() const { return predIndex; }
    vector<Term*> getTerms() const { return terms; }
    bool isTrueNegated() const { return trueNegated; } 
    bool isPropositional() const { return (terms.size() == 0); }
    
private:
    friend inline ostream& operator<< ( ostream&, const Atom& );
    
    static vector<string> predicateNames;
    static vector<unsigned> arities;
    static vector<string> stringConstants;
    static vector<int> integerConstants;
    
    unsigned predIndex;
    bool trueNegated;
    vector<Term*> terms;
};

ostream& 
operator<< ( 
    ostream & out, 
    const Atom& a )
{
    if( a.trueNegated )
        out << "-";
    out << Atom::getPredicateName(a.predIndex);
    if( a.terms.size() != 0 ) 
    {
        out << "(";
        for( unsigned i=0; i<a.terms.size(); i++ )
        {
            out << a.terms[i]->toString();
            if( i < a.terms.size()-1 )
                out << ",";
        }
        out << ")";
    }
    return out;
}

#endif	/* ATOM_H */

