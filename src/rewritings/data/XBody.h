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
 * File:   XBody.h
 * Author: pierfrancesco
 *
 * Created on 28 ottobre 2014, 17.13
 */

#ifndef XBODY_H
#define XBODY_H

#include <unordered_set>
#include <vector>
#include "XLiteral.h"

namespace DLV2{ namespace REWRITERS{

    class XBody {
    public:
        typedef typename std::unordered_set< XLiteral >::const_iterator const_iterator;

        XBody( const XBody& body );
        virtual ~XBody();

        const_iterator begin() const { return literals.begin(); }
        const_iterator end() const { return literals.end(); }
        size_t size() const { return literalPtrs.size(); }
        const XLiteral& operator[]( index_t index ) const;
        void addLiteral( const XLiteral& literal );

    protected:
        std::unordered_set< XLiteral > literals;
        std::vector< const_iterator > literalPtrs;

    private:
        friend std::ostream& operator<< ( std::ostream&, const XBody& );
        friend class XProgram;

        XBody(): literals(), literalPtrs() { }
        XBody( const std::unordered_set< XLiteral >& atoms2 );

    };

};};


#endif /* XBODY_H */
