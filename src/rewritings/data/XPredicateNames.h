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
 * File:   XPredicateNames.h
 * Author: pierfrancesco
 *
 * Created on 27 ottobre 2014, 18.02
 */

#ifndef XPREDICATENAMES_H
#define XPREDICATENAMES_H


#include "XNamesTable.h"
#include "XNamesItem.h"
#include <vector>

namespace DLV2{ namespace REWRITERS{

    class XPredicateNames {
    public:
        typedef XNamesTable< XNamesItem >::const_iterator const_iterator;

        XPredicateNames( const XPredicateNames& pn2 );
        ~XPredicateNames() { }

        XPredicateNames& operator=( const XPredicateNames& pn2 );

        unsigned getStartIndex() const { return startIndex; }
        unsigned getArity( index_t index ) const;
        const std::string& getName( index_t index ) const;
        bool isInternal( index_t index ) const;
        void print( index_t index, std::ostream& o ) const;
        const XNamesItem& getItem( index_t index ) const;
        bool isValidIndex( index_t index ) const;

        std::pair< index_t, bool > add( const char* name, unsigned arity, bool internal = false );
        std::pair< index_t, bool > add( const std::string& name, unsigned arity, bool internal = false );
        std::pair< index_t, bool > find( const XNamesItem& n ) const { return preds.find(n); }
        std::pair< index_t, bool > find( const char* ns, unsigned ar ) const { return find(XNamesItem(ns,ar)); }
        std::pair< index_t, bool > find( const std::string& ns, unsigned ar ) const { return find(XNamesItem(ns,ar)); }
        size_t size() const { return preds.size(); }
        const_iterator begin() const { return preds.begin(); }
        const_iterator end() const { return preds.end(); }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XPredicateNames& );
        friend class XProgram;

        XPredicateNames( unsigned startIdx = 0 ): startIndex(startIdx), preds(startIdx), internal() { }

        unsigned startIndex;
        XNamesTable< XNamesItem > preds;
        // internal[i] is true if i is the index of an internally defined name;
        // false, otherwise.
        std::vector< bool > internal;

    };

    inline
    std::ostream&
    operator<< (
        std::ostream& out,
        const XPredicateNames& pn )
    {
        out << "PREDICATE NAMES TABLE (predicate --> predicate index):" << std::endl;
        for( XPredicateNames::const_iterator it = pn.begin();
                it != pn.end();
                it++ )
        {
            out << *it << " --> " << it.getIndex() << std::endl;
        }
        return out;
    }

};};


#endif /* XPREDICATENAMES_H */
