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
 * File:   XNullsetTable.h
 * Author: pierfrancesco
 *
 * Created on 26 giugno 2015, 19.21
 */

#ifndef XNULLSETTABLE_H
#define XNULLSETTABLE_H

#include <unordered_map>

#include "XPredicateNullsets.h"

namespace DLV2{ namespace REWRITERS{

    class XProgram;

    class XNullsetTable {
    public:
        typedef std::unordered_map< index_t, XPredicateNullsets >::const_iterator const_iterator;
        typedef std::unordered_map< index_t, XPredicateNullsets >::iterator iterator;

        XNullsetTable( const XNullsetTable& nTable ): nullsetsMap(nTable.nullsetsMap), program(nTable.program) { assert(0); }
        ~XNullsetTable() { }

        XPredicateNullsets& operator[]( index_t predIdx );
        const XPredicateNullsets& at( index_t predIdx ) const;
        std::pair< iterator, bool > insert( index_t predIdx, const XPredicateNullsets& predNullsets );
        const_iterator find( index_t predIdx ) const { return nullsetsMap.find(predIdx); }
        bool isEmpty( index_t predIdx, unsigned pos ) const;
        void clear() { nullsetsMap.clear(); }
        const_iterator begin() const { return nullsetsMap.begin(); }
        const_iterator end() const { return nullsetsMap.end(); }

    private:
        friend class XProgram;

        XNullsetTable( const XProgram& p ): nullsetsMap(), program(p) { }

        std::unordered_map< index_t, XPredicateNullsets > nullsetsMap;
        const XProgram& program;
    };

};};

#endif /* XNULLSETTABLE_H */
