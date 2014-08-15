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
#include "../util/Assert.h"

namespace DLV2{ namespace MOCK{

    class Atom {
    public:
        //Atom() { }
        Atom( std::string, unsigned, std::vector<Term>, bool tNeg = false );
        Atom( std::string, unsigned, std::vector<Term>, std::vector<Term> );
        Atom( Term* left, std::string bop, Term* right );
        Atom( const Atom& a );
        ~Atom();

        std::string getPredName() const; 
        unsigned getIndex() const { return predIndex; }
        unsigned getPredicateArity( unsigned ) { return arity; }
        std::vector<Term> getTerms() const { return terms; }
        bool isTrueNegated() const { return trueNegated; } 
        bool isPropositional() const { return (terms.size() == 0); }
        bool isExistential() const { return (existentialVars.size() > 0); }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const Atom& );

        unsigned predIndex;
        unsigned arity;
        bool trueNegated;
        std::vector<Term> terms;
        std::vector<Term> existentialVars;

        bool isBuiltin;
        Term* bLeft;
        std::string binop;
        Term* bRight;
    };

    inline
    std::ostream& 
    operator<< ( 
        std::ostream & out, 
        const Atom& a )
    {
        if( a.isBuiltin )
        {
            assert_msg( (a.bLeft != NULL && a.bRight != NULL),
                "Invalid builtin atom, null terms");
            out << *(a.bLeft) << a.binop << *(a.bRight);
        }
        else
        {
            if( a.existentialVars.size() > 0 )
            {
                out << "\\E ";
                for( unsigned i=0; i<a.existentialVars.size(); i++ )
                {
                    out << a.existentialVars[i];
                    if( i < a.existentialVars.size()-1 )
                        out << ",";
                }
                out << " ";
            }
            if( a.trueNegated )
                out << "-";
            out << a.getPredName();
            if( a.terms.size() != 0 ) 
            {
                out << "(";
                for( unsigned i=0; i<a.terms.size(); i++ )
                {
                    out << a.terms[i];
                    if( i < a.terms.size()-1 )
                        out << ",";
                }
                out << ")";
            }
        }
        return out;
    }

};};

#endif	/* ATOM_H */

