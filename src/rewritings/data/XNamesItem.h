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
 * File:   XNamesItem.h
 * Author: pierfrancesco
 *
 * Created on 27 ottobre 2014, 17.27
 */

#ifndef XNAMESITEM_H
#define XNAMESITEM_H

#include <cstring>
#include "../../util/Assert.h"

namespace DLV2{ namespace REWRITERS{

    class XNamesItem
    {
    public:
        XNamesItem( const XNamesItem &item2 );

        void operator=(const XNamesItem&) { assert( 0 ); }
        bool operator==(const XNamesItem &n) const;
        bool operator!=(const XNamesItem &n) const;

        const std::string& getNameAsString() const { return name; }
        const char* getName() const { return name.c_str(); }
        unsigned getArity() const { return arity; }
        /**
         * @return whether this name designates a positive predicate.
         */
        bool isPositive() const { return !isNegative(); }
        /** Checks for true negation.
         * @return whether this name designates a (truly) negative predicate.
         */
        bool isNegative() const { return getName()[0] == '-'; }
        /** Provides the positive form of this name.
         * @return the name without any leading negation symbols.
         */
        const char* getPositiveName() const;
        /** Provides the negative form of this name.  This is relatively
         *  inefficient compared to getPositiveName() and should be avoided
         *  where possible.
         * @return the name with a leading negation symbol. The name is allocated
         *         in any case and should be deallocated by the caller.
         */
        const char* getNegativeName() const;

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XNamesItem& );
        friend class XProgram;
        friend class XPredicateNames;

        XNamesItem(): name(), arity(0) { assert( 0 ); }
        XNamesItem( const std::string& name2, unsigned arity2 ): name(name2), arity(arity2) { }
        XNamesItem( const char *name2, unsigned arity2 ): name(name2), arity(arity2) { }

        // In the ASP standard, each predicate is identified by a pair <name,arity>
        std::string name;
        unsigned arity;

    };

    inline
    std::ostream&
    operator<< (
        std::ostream& out,
        const XNamesItem& item )
    {
        return out << "(" << item.getNameAsString() << "," << item.getArity() << ")";
    }

};};

namespace std
{
    template <>
    struct hash< DLV2::REWRITERS::XNamesItem >
    {
        size_t operator()(const DLV2::REWRITERS::XNamesItem& n) const
        {
            // Compute individual hash values for two data members
            // and combine them using XOR and bit shifting.
            return ((hash< string >()(n.getNameAsString())
                    ^ (hash< unsigned >()(n.getArity()) << 1)) >> 1);
        }
    };
}

inline
bool
operator<(
    const DLV2::REWRITERS::XNamesItem& n1,
    const DLV2::REWRITERS::XNamesItem& n2 )
{
    int ret = strcmp(n1.getName(),n2.getName());
    if( ret == 0 )
        return n1.getArity() < n2.getArity();
    else
        return ret < 0;
}



#endif /* XNAMESITEM_H */
