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
 * File:   DBLiteral.h
 * Author: pierfrancesco
 *
 * Created on 29 luglio 2014, 16.15
 */

#ifndef DBLITERAL_H
#define	DBLITERAL_H

#include "DBAtom.h"
#include "DBAggregateElement.h"

namespace DLV2{ namespace DB{
    
    class DBAggregateElement;
    inline std::ostream& operator<< ( std::ostream&, const DBAggregateElement& );

    class DBLiteral {
    public:
        DBLiteral( const DBLiteral& l );
        ~DBLiteral();

        bool isNaf() const { return isNegative; }
        bool isBuiltin() const;
        DBAtom* getAtom() const { return atom; }
        bool isAggregate() const { return aggregate; }
        DBTerm* getAggregateLowerGuard() const { return lowerGuard; }
        const std::string& getAggregateLowerBinop() const { return lowerBinop; }
        DBTerm* getAggregateUpperGuard() const { return upperGuard; }
        const std::string& getAggregateUpperBinop() const { return upperBinop; }
        const std::string& getAggregateFunction() const { return aggregateFunction; }
        const std::vector<DBAggregateElement*>& getAggregateElements() const { return aggregateElements; }
        const std::string& getAggregateName() const { return aggregateNameForDepGraph; }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const DBLiteral& );
        friend class DBProgram;
        
        // Only class Program can create Literal objects.
        // Classic literal constructor
        DBLiteral( DBAtom* a, bool neg = false );
        // Aggregate constructor
        DBLiteral( 
            DBTerm*, 
            const std::string&, 
            DBTerm*, const std::string&, 
            const std::string&, 
            const std::vector<DBAggregateElement*>&, 
            bool neg = false,
            const std::string& aggregateName = "" );
        void setIsNaf( bool isNaf ) { isNegative = isNaf; }
        
        DBAtom* atom;
        bool isNegative;

        bool aggregate;
        DBTerm* lowerGuard;
        std::string lowerBinop;
        DBTerm* upperGuard;
        std::string upperBinop;
        std::string aggregateFunction;
        std::vector<DBAggregateElement*> aggregateElements;
        std::string aggregateNameForDepGraph;
    };

    inline
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const DBLiteral& l )
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
                out << *(l.aggregateElements[i]);
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

#endif	/* DBLITERAL_H */

