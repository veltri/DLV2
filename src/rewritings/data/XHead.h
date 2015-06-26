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
 * File:   XHead.h
 * Author: pierfrancesco
 *
 * Created on 28 ottobre 2014, 13.01
 */

#ifndef XHEAD_H
#define XHEAD_H

#include "XAtom.h"
#include <vector>

namespace DLV2{ namespace REWRITERS{

    class XHead {
    public:
        typedef typename std::vector< XAtom >::const_iterator const_iterator;

        XHead( const XHead& head );
        virtual ~XHead();

        const_iterator begin() const { return atoms.begin(); }
        const_iterator end() const { return atoms.end(); }
        size_t size() const { return atoms.size(); }
        const XAtom& operator[]( index_t index ) const;
        const XAtom& at( index_t index ) const;
        void clear() { atoms.clear(); }
        const std::vector< XAtom > getAtoms() const { return atoms; }

        virtual void addAtom( const XAtom& atom );
        bool isGround() const;
        virtual bool isAtomic() const = 0;
        virtual bool isDisjunctive() const = 0;
        virtual bool isConjunctive() const = 0;

        bool operator==( const XHead& head ) const;
        bool operator!=( const XHead& head ) const;

    protected:
        friend class XProgram;

        XHead(): atoms() { }
        XHead( const std::vector< XAtom >& atoms2 );

        std::vector< XAtom > atoms;

    };

};};


#endif /* XHEAD_H */
