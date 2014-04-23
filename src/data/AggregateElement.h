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
 * Created on 2 aprile 2014, 12.30
 */

#ifndef AGGREGATEELEMENT_H
#define	AGGREGATEELEMENT_H

#include <vector>
#include "Literal.h"

namespace DLV2
{

    class Literal;
    inline ostream& operator<< ( ostream&, const Literal& );
    
    class AggregateElement {
    public:
        AggregateElement( vector<Term> t, vector<Literal> lits ): terms(t), literals(lits) { }
        AggregateElement( const AggregateElement& ae ): terms(ae.terms), literals(ae.literals) { }
        ~AggregateElement() { }

        void addLiteral( const Literal& l ) { literals.push_back(l); }

    private:
        friend inline ostream& operator<< ( ostream&, const AggregateElement& );

        vector<Term> terms;
        vector<Literal> literals;
    };

    inline ostream& operator<< ( ostream& out, const AggregateElement& ae )
    {
        for( unsigned i=0; i<ae.terms.size(); i++ )
        {
            out << ae.terms[i];
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

};

#endif	/* AGGREGATEELEMENT_H */

