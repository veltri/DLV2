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
 * File:   DBPredicateNames.h
 * Author: pierfrancesco
 *
 * Created on 30 agosto 2014, 14.58
 */

#ifndef DBPREDICATENAMES_H
#define	DBPREDICATENAMES_H

#include "DBNamesTable.h"
#include "DBNamesItem.h"
#include <vector>

namespace DLV2{ namespace DB{
  
    class DBPredicateNames {
    public:
        typedef DBNamesTable< DBNamesItem >::const_iterator const_iterator;
        
        DBPredicateNames( unsigned startIdx = 0 ): startIndex(startIdx), preds(startIdx), internal() { }
        DBPredicateNames( const DBPredicateNames& pn2 );
        ~DBPredicateNames() { }

        DBPredicateNames& operator=( const DBPredicateNames& pn2 );

        unsigned getStartIndex() const { return startIndex; }
        unsigned getArity( index_t index ) const;
        const std::string& getName( index_t index ) const;
        bool isInternal( index_t index ) const;
        void print( index_t index, std::ostream& o ) const;
        const DBNamesItem& getItem( index_t index ) const;
        
        std::pair< index_t, bool > add( const char* name, unsigned arity, bool internal = false );
        std::pair< index_t, bool > add( const std::string& name, unsigned arity, bool internal = false );
        std::pair< index_t, bool > find( const DBNamesItem& n ) const { return preds.find(n); }
        std::pair< index_t, bool > find( const char* ns, unsigned ar ) const { return find(DBNamesItem(ns,ar)); }
        std::pair< index_t, bool > find( const std::string& ns, unsigned ar ) const { return find(DBNamesItem(ns,ar)); }
        size_t size() const { return preds.size(); }
        const_iterator begin() const { return preds.begin(); }
        const_iterator end() const { return preds.end(); }
        
    private:
        friend inline std::ostream& operator<< ( std::ostream&, const DBPredicateNames& );
        
        unsigned startIndex;
        DBNamesTable< DBNamesItem > preds;
        // internal[i] is true if i is the index of an internally defined name;
        // false, otherwise.  
        std::vector< bool > internal;
        
    };
    
    inline
    std::ostream&
    operator<< (
        std::ostream& out,
        const DBPredicateNames& pn )
    {
        out << "PREDICATE NAMES TABLE (predicate --> predicate index):" << std::endl;
        for( DBPredicateNames::const_iterator it = pn.begin();
                it != pn.end();
                it++ )
        {
            out << *it << " --> " << it.getIndex() << std::endl;
        }
        return out;
    }
    
};};

#endif	/* DBPREDICATENAMES_H */

