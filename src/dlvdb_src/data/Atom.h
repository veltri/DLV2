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
 * Created on 28 luglio 2014, 19.02
 */

#ifndef ATOM_H
#define	ATOM_H

#include "Term.h"

namespace DLV2{ namespace DB{
    
    class Atom {
        Atom( const Atom& );
        ~Atom() { }
        
        const std::string& getPredicateName() { return predicateName; }
        unsigned getArity() { return arity; }
        bool isTrueNegated() { return trueNegated; }
        const std::vector<Term>& getTerms() { return terms; } 
        bool isBuiltin() { return isBuiltin; }
        
    private:
        friend inline std::ostream& operator<< ( std::ostream&, const Atom& );
        
        // Only class Program can create Atom objects.
        Atom() { }
        Atom( const std::string& );
        Atom( const std::string&, unsigned, std::vector<Term>, bool tNeg=false );
        //friend class Program;

        std::string predicateName;
        unsigned arity;
        bool trueNegated;
        std::vector<Term> terms;
        bool isBuiltin;
    };
    
    inline
    std::ostream& 
    operator<< ( 
        std::ostream & out, 
        const Atom& a )
    {
        if( a.isBuiltin )
        {
            out << a.predicateName;
        }
        else
        {
            if( a.trueNegated )
                out << "-";
            out << a.getPredicateName();
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

