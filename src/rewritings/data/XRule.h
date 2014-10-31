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
 * File:   XRule.h
 * Author: pierfrancesco
 *
 * Created on 29 ottobre 2014, 15.48
 */

#ifndef XRULE_H
#define XRULE_H

#include "XHead.h"
#include "XBody.h"

namespace DLV2{ namespace REWRITERS{

    class XRule {
    public:
        XRule( const XRule& rule );
        ~XRule();

        const XHead* getHead() const { return head; }
        const XBody* getBody() const { return body; }
        bool hasNegation();
        bool hasAtomicHead() const;
        bool hasDisjunctiveHead() const;
        bool hasConjunctiveHead() const;
        bool isRecursive() const;
        bool isGround() const;

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XRule& );
        friend class XProgram;

        XRule(): head(NULL), body(NULL), naf(false), recursion(false) { assert(0); }
        XRule( XHead* head, XBody* body );
        // The recursive flag could be set after that the dependency graph
        // has been computed, hence after the creation of the rule itself.
        void setRecursive( bool rec ) { recursion = rec; }

        XHead* head;
        XBody* body;
        int naf;
        int recursion;

    };

    inline
    std::ostream&
    operator<< (
        std::ostream& out,
        const XRule& r )
    {
        assert_msg( r.head != NULL, "Rules must have at least the head" );
        if( r.hasDisjunctiveHead() )
        {
            for( unsigned i=0; i<r.head->size(); i++ )
            {
                out << (*r.head)[i] << " ";
                if( i<r.head->size()-1 )
                    out << "| ";
            }
        }
        else if( r.hasConjunctiveHead() )
        {
            for( unsigned i=0; i<r.head->size(); i++ )
            {
                out << (*r.head)[i] << " ";
                if( i<r.head->size()-1 )
                    out << "^ ";
            }
        }
        else
        {
            assert_msg( r.head->size() == 1, "Atomic heads must have exactly one atom" );
            out << (*r.head)[0] << " ";
        }
        if( r.body != NULL && r.body->size() > 0 )
        {
            out << ":- ";
            for( unsigned i=0; i<r.body->size(); i++ )
            {
                out << (*r.body)[i];
                if( i<r.body->size()-1 )
                    out << ", ";
            }
        }
        out << ".";
        return out;
    }

};};

#endif /* XRULE_H */
