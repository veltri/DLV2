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
#include <list>

namespace DLV2{ namespace REWRITERS{

    class XRule {
    public:
        typedef std::list< XRule >::iterator iterator;
        typedef std::list< XRule >::const_iterator const_iterator;

        XRule( const XRule& rule );
        ~XRule();

        const XHead* getHead() const { return head; }
        const XBody* getBody() const { return body; }
        bool isExistential( const XTerm& var ) const;
        bool hasNegation();
        bool hasAtomicHead() const;
        bool hasDisjunctiveHead() const;
        bool hasConjunctiveHead() const;
        bool hasExistentialVariables() const { return existVars.size() > 0; }
        bool isRecursive() const;
        bool isGround() const;

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XRule& );
        friend class XProgram;

        XRule(): head(NULL), body(NULL), existVars(), naf(false), recursive(false) { assert(0); }
        XRule( XHead* head, XBody* body );
        // The recursive flag could be set after that the dependency graph
        // has been computed, hence after the creation of the rule itself.
        void setRecursive( bool rec ) { recursive = rec; }

        XHead* head;
        XBody* body;
        std::unordered_set< XTerm > existVars;
        int naf;
        int recursive;

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

// FIXME: ask giorgio to check it..
namespace std {

    template <>
    struct hash< DLV2::REWRITERS::XRule >
    {
        size_t operator()( const DLV2::REWRITERS::XRule& rule ) const
        {
            std::hash< DLV2::REWRITERS::XAtom > atomHasher;
            assert_msg( rule.getHead() != NULL, "Null head" );
            size_t h = 1;
            for( unsigned i=0; i<rule.getHead()->size(); i++ )
                h = h*5+atomHasher(rule.getHead()->at(i));
            if( rule.getBody() != NULL )
            {
                std::hash< DLV2::REWRITERS::XLiteral > litHasher;
                for( unsigned i=0; i<rule.getBody()->size(); i++ )
                    h = h*5+litHasher(rule.getBody()->at(i));
            }
            return h;
        }
    };

    template <>
    struct hash< DLV2::REWRITERS::XRule::const_iterator >
    {
        size_t operator()( const DLV2::REWRITERS::XRule::const_iterator& it ) const
        {
            std::hash< DLV2::REWRITERS::XRule > ruleHasher;
            return ruleHasher(*it);
        }
    };
};


#endif /* XRULE_H */
