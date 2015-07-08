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
 * File:   XNullset.h
 * Author: pierfrancesco
 *
 * Created on 27 giugno 2015, 12.51
 */

#ifndef XNULLSET_H
#define XNULLSET_H

#include "XRandomAccessSet.h"

namespace DLV2{ namespace REWRITERS{

    class XNullset {
    public:
        XNullset( const XNullset& nullset ): nullIndexes(nullset.nullIndexes) { }
        ~XNullset() { }

        size_t size() const { return nullIndexes.size(); }
        const index_t& operator[]( index_t pos ) const { return nullIndexes[pos]; }
        const index_t& at( index_t pos ) const { return nullIndexes.at(pos); }
        void pushNull( index_t n ) { nullIndexes.pushItem(n); }
        bool find( index_t n ) const { return nullIndexes.find(n); }
        bool empty() const { return nullIndexes.size() == 0; }
        void clear() { nullIndexes.clear(); }

    private:
        friend class XProgram;
        friend class XPredicateNullsets;

        XNullset(): nullIndexes() { }

        XRandomAccessSet< index_t > nullIndexes;

    };

};};

#endif /* XNULLSET_H */
