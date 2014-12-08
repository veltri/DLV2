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
 * File:   XLiteral.h
 * Author: pierfrancesco
 *
 * Created on 28 ottobre 2014, 12.51
 */

#ifndef XLITERAL_H
#define XLITERAL_H

#include "../../util/Assert.h"
#include "XAtom.h"

namespace DLV2{ namespace REWRITERS{

    class XLiteral {
    public:
        XLiteral( const XLiteral& l );
        ~XLiteral();

        const XAtom& getAtom() const { return atom; }
        bool isNaf() const { return isNegative; }
        bool isPropositional() const { return atom.isPropositional(); }
        bool isGround() const { return atom.isGround(); }
        /** Determines if this XLiteral can save others.
         * No, this is not the beginning of a religion.
         * @return true whether this can provide safety.
         */
        bool isSaviour() const;
        bool operator==( const XLiteral& literal ) const;
        bool operator!=( const XLiteral& literal ) const;

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XLiteral& );
        friend class XProgram;

        // Only class XProgram can create XLiteral objects.
        XLiteral( const XAtom& a, bool neg = false );
        void setIsNaf( bool isNaf ) { isNegative = isNaf; }

        XAtom atom;
        bool isNegative;
    };

    inline
    std::ostream&
    operator<< (
        std::ostream& out,
        const XLiteral& l )
    {
        if( l.isNegative )
                out << "not ";
        out << l.atom;
        return out;
    }

};};

// FIXME: ask giorgio to check it..
namespace std {

    template <>
    struct hash< DLV2::REWRITERS::XLiteral >
    {
        size_t operator()( const DLV2::REWRITERS::XLiteral& literal ) const
        {
            std::hash< DLV2::REWRITERS::XAtom > atomHasher;
            size_t h = atomHasher(literal.getAtom());
            if( literal.isNaf() )
            {
                std::hash< std::string > strHasher;
                h = h*5+strHasher("not");
            }
            return h;
        }
    };

};


#endif /* XLITERAL_H */
