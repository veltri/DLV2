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
#include "../../util/Assert.h"
#include <vector>

namespace DLV2{ namespace DB{
    
    class Atom {
    public:
        Atom( const Atom& );
        ~Atom();
        
        const std::string& getPredicateName() const { return predicateName; }
        unsigned getArity() const { return arity; }
        bool isTrueNegated() const { return trueNegated; }
        const std::vector<Term>& getTerms() const { return terms; } 
        bool isBuiltin() const { return builtin; }
        const Term& getLeftOperand() const { return *leftOp; }
        const std::string& getBinaryOperator() const { return binOp; }
        const Term& getRightOperand() const { return *rightOp; }
        
    private:
        friend inline std::ostream& operator<< ( std::ostream&, const Atom& );
        friend class Program;
        
        // Only class Program can create Atom objects.
        Atom() { }
        Atom( const Term& leftOp, const std::string& binOp, const Term& rightOp );
        Atom( const std::string& predName, const std::vector<Term>& terms, bool tNeg=false );

        std::string predicateName;
        unsigned arity;
        bool trueNegated;
        std::vector<Term> terms;
        bool builtin;
        Term* leftOp;
        std::string binOp;
        Term* rightOp;
    };
    
    inline
    std::ostream& 
    operator<< ( 
        std::ostream & out, 
        const Atom& a )
    {
        if( a.builtin )
        {
            assert_msg( (a.leftOp != NULL && a.rightOp != NULL),
                "Invalid builtin atom, null terms");
            out << *(a.leftOp) << a.binOp << *(a.rightOp);
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

