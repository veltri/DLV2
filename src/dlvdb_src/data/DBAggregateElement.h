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
 * File:   DBAggregateElement.h
 * Author: cesco
 *
 * Created on 29 luglio 2014, 16.54
 */

#ifndef DBAGGREGATEELEMENT_H
#define	DBAGGREGATEELEMENT_H

#include <vector>
#include "DBLiteral.h"

namespace DLV2{ namespace DB{

    class DBLiteral;
    inline std::ostream& operator<< ( std::ostream&, const DBLiteral& );
    
    class DBAggregateElement {
    public:
        DBAggregateElement( const DBAggregateElement& ae ): terms(ae.terms), literals(ae.literals) { }
        ~DBAggregateElement();

        const std::vector<DBTerm*>& getTerms() const { return terms; }
        const std::vector<DBLiteral*>& getLiterals() const { return literals; }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const DBAggregateElement& );
        friend class DBProgram;
        
        // Only class Program can create AggregateElement objects.
        DBAggregateElement( const std::vector<DBTerm*>& t, const std::vector<DBLiteral*>& lits ): terms(t), literals(lits) { }
        void addLiteral( DBLiteral* l ) { if( l != NULL ) literals.push_back(l); }
        void addTerm( DBTerm* t ) { if( t != NULL ) terms.push_back(t); }

        std::vector<DBTerm*> terms;
        std::vector<DBLiteral*> literals;
    };

    inline 
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const DBAggregateElement& ae )
    {
        for( unsigned i=0; i<ae.terms.size(); i++ )
        {
            if( ae.terms[i] != NULL )
            {
                out << *(ae.terms[i]);
                if( i < ae.terms.size()-1 )
                    out << ",";
            }
        }
        if( ae.literals.size() > 0 )
            out << ":";
        for( unsigned i=0; i<ae.literals.size(); i++ )
        {
            if( ae.literals[i] != NULL )
            {
                out << *(ae.literals[i]);
                if( i < ae.literals.size()-1 )
                    out << ",";
            }
        }
        return out;
    }

};};

#endif	/* DBAGGREGATEELEMENT_H */

