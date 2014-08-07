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
 * File:   Literal.h
 * Author: pierfrancesco
 *
 * Created on 29 luglio 2014, 16.15
 */

#ifndef LITERAL_H
#define	LITERAL_H

#include "Atom.h"
#include "AggregateElement.h"

namespace DLV2{ namespace DB{
    
    class AggregateElement;
    inline std::ostream& operator<< ( std::ostream&, const AggregateElement& );

    class Literal {
    public:
        Literal( const Literal& l );
        ~Literal();

        bool isNaf() const { return isNegative; }
        const Atom& getAtom() const { return *atom; }
        bool isAggregate() const { return aggregate; }
        const Term& getAggregateLowerGuard() const { return *lowerGuard; }
        const std::string& getAggregateLowerBinop() const { return lowerBinop; }
        const Term& getAggregateUpperGuard() const { return *upperGuard; }
        const std::string& getAggregateUpperBinop() const { return upperBinop; }
        const std::string& getAggregateFunction() const { return aggregateFunction; }
        const std::vector<AggregateElement>& getAggregateElements() const { return aggregateElements; }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const Literal& );
        friend class Program;
        
        // Only class Program can create Literal objects.
        // Classic literal constructor
        Literal( const Atom& a, bool neg = false );
        // Aggregate constructor
        Literal( Term*, const std::string&, Term*, const std::string&, const std::string&, const std::vector<AggregateElement>&, bool neg = false );
        void setIsNaf( bool isNaf ) { isNegative = isNaf; }
        
        Atom* atom;
        bool isNegative;

        bool aggregate;
        Term* lowerGuard;
        std::string lowerBinop;
        Term* upperGuard;
        std::string upperBinop;
        std::string aggregateFunction;
        std::vector<AggregateElement> aggregateElements;
    };

    inline
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const Literal& l )
    {
        if( l.isNegative )
                out << "not ";
        if( l.aggregate )
        {
            assert_msg( (l.lowerGuard != NULL || l.upperGuard != NULL),
                "Invalid aggregate literal, null guards");
            if( l.lowerGuard )
                out << *(l.lowerGuard) << l.lowerBinop;
            out << l.aggregateFunction << "{";
            for( unsigned i=0; i<l.aggregateElements.size(); i++ )
            {
                out << l.aggregateElements[i];
                if( i < l.aggregateElements.size()-1 )
                    out << ";";
            }
            out << "}";
            if( l.upperGuard )
                out << l.upperBinop << *(l.upperGuard);
        }
        else
        {
            assert_msg( l.atom != NULL, "Invalid literal: null atom!");
            out << *(l.atom);
        }
        return out;
    }

};};

#endif	/* LITERAL_H */

