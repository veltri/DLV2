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
 * File:   Rule.h
 * Author: pierfrancesco
 *
 * Created on 29 luglio 2014, 17.42
 */

#ifndef RULE_H
#define	RULE_H

#include "Literal.h"

namespace DLV2{ namespace DB{
    
    class Rule {
    public:
        Rule( const Rule& r ): head(r.head), body(r.body) { } 
        ~Rule();

        const std::vector<Atom*>& getHead() const { return head; }
        const std::vector<Literal*>& getBody() const { return body; }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const Rule& );
        friend class Program;
        
        // Only class Program can create Rule objects.
        Rule( const std::vector<Atom*>& h, const std::vector<Literal*>& b ): head(h), body(b) { }
        void addToHead( Atom* a ) { head.push_back(a); }
        void addToBody( Literal* l ) { body.push_back(l); }

        std::vector<Atom*> head;
        std::vector<Literal*> body;
    };

    inline
    std::ostream& 
    operator<< ( 
        std::ostream& out,
        const Rule& r )
    {
        for( unsigned i=0; i<r.head.size(); i++ )
        {
            out << *(r.head[i]);
            if( i<r.head.size()-1 )
                out << " | ";
        }
        if( r.head.size() > 0 && r.body.size() > 0 )
            out << " :- ";
        else if( r.body.size() > 0 )
            out << ":- ";
        for( unsigned i=0; i<r.body.size(); i++ )
        {
            out << *(r.body[i]);
            if( i<r.body.size()-1 )
                out << ", ";
        }
        out << ".";
        return out;
    }
    
};};

#endif	/* RULE_H */

