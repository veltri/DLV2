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
 * File:   WeakConstraint.h
 * Author: cesco
 *
 * Created on 25 marzo 2014, 13.35
 */

#ifndef WEAKCONSTRAINT_H
#define	WEAKCONSTRAINT_H

#include <vector>
#include "Literal.h"

namespace DLV2{ namespace MOCK{

    class WeakConstraint {
    public:
        WeakConstraint( std::vector<Literal> b, Term* w, Term* l, std::vector<Term> t );
        WeakConstraint( const WeakConstraint& wc );
        ~WeakConstraint();

        void addToBody( const Literal& l ) { body.push_back(l); }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const WeakConstraint& );

        std::vector<Literal> body;
        Term* weight;
        Term* level;
        std::vector<Term> terms;
    };

    inline
    std::ostream& 
    operator<< ( 
        std::ostream& out,
        const WeakConstraint& wc )
    {
        out << ":~ ";
        for( unsigned i=0; i<wc.body.size(); i++ )
        {
            out << wc.body[i];
            if( i<wc.body.size()-1 )
                out << ", ";
        }
        out << ".";

        if( wc.weight || wc.level || wc.terms.size() > 0 )
        {
            out << " [";
            if( wc.weight )
                out << *(wc.weight);
            if( wc.level )
                out << "@" << *(wc.level);
            for( unsigned i=0; i<wc.terms.size(); i++ )
            {
                if( (i == 0 && wc.weight) || i > 0 )
                    out << ",";
                out << wc.terms[i];
            }
            out << "]";
        }

        return out;
    }

};};

#endif	/* WEAKCONSTRAINT_H */

