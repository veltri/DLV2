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
        DBRule( const DBRule& r ): head(r.head), body(r.body) { } 
        ~DBRule();

        const std::vector<DBAtom*>& getHead() const { return head; }
        const std::vector<DBLiteral*>& getBody() const { return body; }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const DBRule& );
        friend class DBProgram;
        
        // Only class Program can create Rule objects.
        DBRule( const std::vector<DBAtom*>& h, const std::vector<DBLiteral*>& b ): head(h), body(b) { }
        void addToHead( DBAtom* a ) { if( a != NULL ) head.push_back(a); }
        void addToBody( DBLiteral* l ) { if( l != NULL ) body.push_back(l); }

        std::vector<DBAtom*> head;
        std::vector<DBLiteral*> body;
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

