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
 * File:   XAtom.h
 * Author: pierfrancesco
 *
 * Created on 27 ottobre 2014, 18.28
 */

#ifndef XATOM_H
#define XATOM_H

#include <vector>
#include "../../util/Assert.h"
#include "../../util/Constants.h"
#include "XTerm.h"
#include "XAtomType.h"

namespace DLV2{ namespace REWRITERS{

    class XProgram;

    class XAtom {
    public:
        XAtom( const XAtom& );
        ~XAtom();

        index_t getPredIndex() const { return predIndex; }
        const std::string& getPredicateName() const;
        unsigned getArity() const;
        bool isTrueNegated() const { return trueNegated; }
        const std::vector< XTerm >& getTerms() const { return terms; }
        const XAtomType& getType() const { return type; }
        bool isGround() const;
        bool isPropositional() const { return terms.size() == 0; }
        bool operator==( const XAtom& atom ) const;
        bool operator!=( const XAtom& atom ) const;

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XAtom& );
        friend class XProgram;

        // Only class XProgram can create XAtom objects.
        // Standard constructor
        XAtom(
            const XProgram& ownerProgr,
            index_t predIdx,
            const std::vector< XTerm >& terms,
            bool tNeg = false );

        const XProgram& ownerProgram;
        index_t predIndex;
        bool trueNegated;
        std::vector< XTerm > terms;
        XAtomType type;
    };

    inline
    std::ostream&
    operator<< (
        std::ostream & out,
        const XAtom& a )
    {
        if( a.trueNegated )
            out << "-";
        out << a.getPredicateName();
        if( a.terms.size() != 0 )
        {
            out << "(";
            for( unsigned i=0; i<a.terms.size(); i++ )
            {
                out << a.terms[i];
                if( i < a.terms.size()-1 )
                    out << ",";
            }
            out << ")";
        }
        return out;
    }

};};

// FIXME: ask giorgio to check it..
namespace std {

    template <>
    struct hash< DLV2::REWRITERS::XAtom >
    {
        size_t operator()( const DLV2::REWRITERS::XAtom& atom ) const
        {
            std::hash< std::string > strHasher;
            size_t h = strHasher(atom.getPredicateName());
            for( unsigned i=0; i<atom.getTerms().size(); i++ )
            {
                std::hash< DLV2::REWRITERS::XTerm > termHasher;
                h = h*5+termHasher(atom.getTerms().at(i));
            }
            return h;
        }
    };

};

#endif /* XATOM_H */
