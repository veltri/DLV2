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
#include "../../util/Constants.h"

#include <vector>

namespace DLV2{ namespace DB{
    
    class DBProgram;
    class DBAggregateElement;
    inline std::ostream& operator<< ( std::ostream&, const DBAggregateElement& );
    
    class DBAtom {
    public:
        DBAtom( const DBAtom& );
        ~DBAtom();
        
        index_t getPredIndex() const { assert_msg( !builtin, "Builtins has no predicates." ); return predIndex; }
        const std::string& getPredicateName() const;
        unsigned getArity() const;
        bool isTrueNegated() const { return trueNegated; }
        
        // Standard atoms methods
        const std::vector< DBTerm* >& getTerms() const { return terms; }
        bool isRegularAtom() const { return (!isBuiltin() && !isAggregate()); }
        bool isPropositional() const { return (isRegularAtom() && terms.size() == 0); }
        bool isBuiltin() const { return builtin; }
        bool isAggregate() const { return aggregate; }
        /** An atom is an assignment aggregate if it's an aggregate of the form: 
         * X <= aggregate( Vars : Conjunction ) <= X.
         * @return true whether this atom is an assignment aggregate
         */
        bool isAssignmentAggregate() const;
        /** An atom is an assignment builtin if it's a builtin of the form:
         * X = string/constant | string/constant = X.
         * @return true whether this atom is an assignment builtin
         */
        bool isAssignmentBuiltin() const;
        
        // Builtins methods
        DBTerm* getLeftOperand() const { return leftOp; }
        const std::string& getBinaryOperator() const { return binOp; }
        DBTerm* getRightOperand() const { return rightOp; }
        bool isEqualityBuiltin() const { return isBuiltin() && !binOp.compare("="); }
        
        // Aggregates methods
        DBTerm* getAggregateLowerGuard() const { return lowerGuard; }
        const std::string& getAggregateLowerBinop() const { return lowerBinop; }
        DBTerm* getAggregateUpperGuard() const { return upperGuard; }
        const std::string& getAggregateUpperBinop() const { return upperBinop; }
        const std::string& getAggregateFunction() const { return aggregateFunction; }
        const std::vector<DBAggregateElement*>& getAggregateElements() const { return aggregateElements; }
        const std::string& getAggregateName() const;
        
    private:
        friend std::ostream& operator<< ( std::ostream&, const DBAtom& );
        friend class DBProgram;
        
        // Only class Program can create Atom objects.
        // Standard constructor
        DBAtom( 
            const DBProgram& ownerProgr,
            index_t predIdx,
            const std::vector< DBTerm* >& terms, 
            bool tNeg=false );
        // Builtin constructor
        DBAtom( 
            const DBProgram& ownerProgr,
            DBTerm* leftOp,
            const std::string& binOp,
            DBTerm* rightOp );
        // Aggregate constructor
        DBAtom(
            const DBProgram& ownerProgr,
            index_t predIdx,
            DBTerm* lowerG, 
            const std::string& lowerB, 
            DBTerm* upperG, 
            const std::string& upperB, 
            const std::string& aggrFunct, 
            const std::vector< DBAggregateElement* >& aggreSet );

        const DBProgram& ownerProgram;
        index_t predIndex;
        // Standard atoms
        bool trueNegated;
        std::vector< DBTerm* > terms;
        // Builtin atoms
        bool builtin;
        DBTerm* leftOp;
        std::string binOp;
        DBTerm* rightOp;
        // Aggregate atoms
        bool aggregate;
        DBTerm* lowerGuard;
        std::string lowerBinop;
        DBTerm* upperGuard;
        std::string upperBinop;
        std::string aggregateFunction;
        std::vector< DBAggregateElement* > aggregateElements;
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
            out << *a.leftOp << a.binOp << *a.rightOp;
        }
        else if( a.aggregate )
        {
            assert_msg( (a.lowerGuard != NULL || a.upperGuard != NULL),
                "Invalid aggregate literal, null guards");
            if( a.lowerGuard )
                out << *(a.lowerGuard) << a.lowerBinop;
            out << a.aggregateFunction << "{";
            for( unsigned i=0; i<a.aggregateElements.size(); i++ )
            {
                out << *(a.aggregateElements[i]);
                if( i < a.aggregateElements.size()-1 )
                    out << ";";
            }
            out << "}";
            if( a.upperGuard )
                out << a.upperBinop << *(a.upperGuard);
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

