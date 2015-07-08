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
 * File:   XPredicateNullsets.h
 * Author: pierfrancesco
 *
 * Created on 27 giugno 2015, 13.05
 */

#ifndef XPREDICATENULLSETS_H
#define XPREDICATENULLSETS_H

#include <vector>

#include "XNullset.h"

#include "../../util/Assert.h"

namespace DLV2{ namespace REWRITERS{

    class XPredicateNullsets {
    public:
        XPredicateNullsets( const XPredicateNullsets& pn ): nullsets(pn.nullsets) { }
        ~XPredicateNullsets() { }

        const XNullset& operator[]( index_t pos ) const { return nullsets[pos]; }
        const XNullset& at( index_t pos ) const { return nullsets.at(pos); }
        void insertNull( index_t pos, index_t n ) { assert_msg( pos < nullsets.size(), "Index out of range" ); nullsets[pos].pushNull(n); }
        void clear() { for( XNullset n: nullsets ) n.clear(); }

    private:
        friend class XProgram;
        friend class XNullsetTable;

        XPredicateNullsets( unsigned arity ): nullsets(arity,XNullset()) { }

        // There is a different null-set for each column of the schema.
        std::vector< XNullset > nullsets;

    };

};};

#endif /* XPREDICATENULLSETS_H */
