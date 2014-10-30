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
 * File:   DBRule.h
 * Author: pierfrancesco
 *
 * Created on 29 luglio 2014, 17.42
 */

#ifndef DBRULE_H
#define	DBRULE_H

#include "DBLiteral.h"

namespace DLV2{ namespace DB{
    
    class DBRule {
    public:
        DBRule( const DBRule& r );
        ~DBRule();

        const std::vector< DBAtom* >& getHead() const { return head; }
        const std::vector< DBLiteral* >& getBody() const { return body; }
        bool hasNegation() const { return naf; }
        bool hasAggregates() const { return aggregates; }
        bool hasBuiltins() const { return builtins; }
        bool isDisjunctive() const { return disjunction; }
        bool isRecursive() const;

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const DBRule& );
        friend class DBProgram;
        
        // Only class Program can create Rule objects.
        DBRule(
                const std::vector< DBAtom* >& head,
                const std::vector< DBLiteral* >& body,
                bool isNegative,
                bool hasAggregates,
                bool hasBuiltins,
                bool isDisjunctive );

        void addToHead( DBAtom* a );
        void addToBody( DBLiteral* l );
        // The recursive flag could be set after that the dependency graph
        // has been computed, hence after the creation of the rule itself.
        void setRecursive( bool rec ) { hasRecursion = rec; }

        std::vector< DBAtom* > head;
        std::vector< DBLiteral* > body;
        bool naf;
        bool aggregates;
        bool builtins;
        bool disjunction;
        int hasRecursion;
    };

    inline
    std::ostream& 
    operator<< ( 
        std::ostream& out,
        const DBRule& r )
    {
        for( unsigned i=0; i<r.head.size(); i++ )
        {
            if( r.head[i] != NULL )
            {
                out << *(r.head[i]);
                if( i<r.head.size()-1 )
                    out << " | ";
            }
        }
        if( r.head.size() > 0 && r.body.size() > 0 )
            out << " :- ";
        else if( r.body.size() > 0 )
            out << ":- ";
        for( unsigned i=0; i<r.body.size(); i++ )
        {
            if( r.body[i] != NULL )
            {
                out << *(r.body[i]);
                if( i<r.body.size()-1 )
                    out << ", ";
            }
        }
        out << ".";
        return out;
    }
    
};};

#endif	/* DBRULE_H */

