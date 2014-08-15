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
 * File:   DBAtom.h
 * Author: pierfrancesco
 *
 * Created on 28 luglio 2014, 19.02
 */

#ifndef DBATOM_H
#define	DBATOM_H

#include "DBTerm.h"
#include "../../util/Assert.h"
#include <vector>

namespace DLV2{ namespace DB{
    
    class DBAtom {
    public:
        DBAtom( const DBAtom& );
        ~DBAtom();
        
        const std::string& getPredicateName() const { return predicateName; }
        unsigned getArity() const { return arity; }
        bool isTrueNegated() const { return trueNegated; }
        const std::vector<DBTerm*>& getTerms() const { return terms; } 
        bool isBuiltin() const { return builtin; }
        DBTerm* getLeftOperand() const { return leftOp; }
        const std::string& getBinaryOperator() const { return binOp; }
        DBTerm* getRightOperand() const { return rightOp; }
        
    private:
        friend inline std::ostream& operator<< ( std::ostream&, const DBAtom& );
        friend class DBProgram;
        
        // Only class Program can create Atom objects.
        DBAtom( DBTerm* leftOp, const std::string& binOp, DBTerm* rightOp );
        DBAtom( const std::string& predName, const std::vector<DBTerm*>& terms, bool tNeg=false );
        DBAtom( char* predName, const std::vector<DBTerm*>& terms, bool tNeg=false );

        std::string predicateName;
        unsigned arity;
        bool trueNegated;
        std::vector<DBTerm*> terms;
        bool builtin;
        DBTerm* leftOp;
        std::string binOp;
        DBTerm* rightOp;
    };
    
    inline
    std::ostream& 
    operator<< ( 
        std::ostream & out, 
        const DBAtom& a )
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
                    if( a.terms[i] != NULL )
                    {
                        out << *(a.terms[i]);
                        if( i < a.terms.size()-1 )
                            out << ",";
                    }
                }
                out << ")";
            }
        }
        return out;
    }
    
};};

#endif	/* DBATOM_H */

