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
 * File:   AggregateElement.h
 * Author: cesco
 *
 * Created on 29 luglio 2014, 16.54
 */

#ifndef AGGREGATEELEMENT_H
#define	AGGREGATEELEMENT_H

#include <vector>
#include "Literal.h"

namespace DLV2{ namespace DB{

    class Literal;
    inline std::ostream& operator<< ( std::ostream&, const Literal& );
    
    class AggregateElement {
    public:
        AggregateElement( const AggregateElement& ae ): terms(ae.terms), literals(ae.literals) { }
        ~AggregateElement();

        const std::vector<Term*>& getTerms() const { return terms; }
        const std::vector<Literal*>& getLiterals() const { return literals; }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const AggregateElement& );
        friend class Program;
        
        // Only class Program can create AggregateElement objects.
        AggregateElement( const std::vector<Term*>& t, const std::vector<Literal*>& lits ): terms(t), literals(lits) { }
        void addLiteral( Literal* l ) { literals.push_back(l); }
        void addTerm( Term* t ) { terms.push_back(t); }

        std::vector<Term*> terms;
        std::vector<Literal*> literals;
    };

    inline 
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const AggregateElement& ae )
    {
        for( unsigned i=0; i<ae.terms.size(); i++ )
        {
            out << *(ae.terms[i]);
            if( i < ae.terms.size()-1 )
                out << ",";
        }
        if( ae.literals.size() > 0 )
            out << ":";
        for( unsigned i=0; i<ae.literals.size(); i++ )
        {
            out << ae.literals[i];
            if( i < ae.literals.size()-1 )
                out << ",";
        }
        return out;
    }

};};

#endif	/* AGGREGATEELEMENT_H */

