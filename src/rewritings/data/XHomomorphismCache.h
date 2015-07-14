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
 * File:   XHomomorphismCache.h
 * Author: cesco
 *
 * Created on 22 maggio 2015, 11.57
 */

#ifndef XHOMOMORPHISMCACHE_H
#define XHOMOMORPHISMCACHE_H

#include "XCache.h"
#include "XAtom.h"

namespace DLV2{ namespace REWRITERS{

    class XHomomorphismCache : public XCache< std::pair< const XAtom&, const XAtom& >, bool > {
    public:
        XHomomorphismCache( const XProgram& inputProgram ): cacheMap(), program(inputProgram) { }
        virtual ~XHomomorphismCache() { }

        virtual std::pair< bool, const bool& > inCache( const std::pair< const XAtom&, const XAtom& >& key ) const;
        virtual void cache( const std::pair< const XAtom&, const XAtom& >& key, const bool& value );

    private:
        size_t getCanonicalHash( const XAtom& atom ) const;

        // Keys are atom indices and for each atom index 'k' another map is provided;
        // such a map says, given an atom index 'j', whether 'k' is homomorphic to 'j'.
        std::unordered_map< size_t, std::unordered_map< size_t, bool > > cacheMap;
        const XProgram& program;
    };

};};

#endif /* XHOMOMORPHISMCACHE_H */
