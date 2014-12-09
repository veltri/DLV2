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
 * File:   XStickyLabel.h
 * Author: pierfrancesco
 *
 * Created on 04 novembre 2014, 16.20
 */

#ifndef XSTICKYLABEL_H
#define XSTICKYLABEL_H

#include "XLiteral.h"
#include "../../util/Constants.h"

namespace DLV2{ namespace REWRITERS{

    class XStickyLabel {
    public:
        XStickyLabel( const XStickyLabel& label ): ruleIndex(label.ruleIndex), atom(label.atom) { }
        ~XStickyLabel() { }

        index_t getExpandedRuleIndex() const { return ruleIndex; }
        const XAtom& getAtom() const { return atom; }

        bool operator==( const XStickyLabel& label ) const { return (ruleIndex==label.ruleIndex && atom==label.atom); }
        bool operator!=( const XStickyLabel& label ) const { return !(*this == label); }
    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XStickyLabel& );
        friend class XProgram;

        XStickyLabel( index_t rIndex, const XAtom& at ): ruleIndex(rIndex), atom(at) { }

        index_t ruleIndex;
        XAtom atom;

    };

    inline
    std::ostream&
    operator<< (
        std::ostream& out,
        const XStickyLabel& label )
    {
        out << "<\\sigma_" << label.getExpandedRuleIndex() << "," << label.getAtom() << ">";
        return out;
    }

};};

// FIXME: ask giorgio to check it..
namespace std {

    template <>
    struct hash< DLV2::REWRITERS::XStickyLabel >
    {
        size_t operator()( const DLV2::REWRITERS::XStickyLabel& label ) const
        {
            std::hash< DLV2::REWRITERS::index_t > ruleIndexHasher;
            size_t h = ruleIndexHasher(label.getExpandedRuleIndex());
            std::hash< DLV2::REWRITERS::XAtom > atomHasher;
            h = h*5+atomHasher(label.getAtom());
            return h;
        }
    };

};

#endif /* XSTICKYLABEL_H */
