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
 * File:   XDisjunctiveHead.h
 * Author: pierfrancesco
 *
 * Created on 28 ottobre 2014, 17.10
 */

#ifndef XDISJUNCTIVEHEAD_H
#define XDISJUNCTIVEHEAD_H

#include "XHead.h"

namespace DLV2{ namespace REWRITERS{

    class XDisjunctiveHead: public XHead {
    public:
        XDisjunctiveHead( const XConjunctiveHead& head ): XHead(head) { }
        virtual ~XDisjunctiveHead() { }

        virtual bool isAtomic() const { return false; }
        virtual bool isDisjunctive() const { return true; }
        virtual bool isConjunctive() const { return false; }

    private:
        friend std::ostream& operator<< ( std::ostream&, const XDisjunctiveHead& );
        friend class XProgram;

        XDisjunctiveHead(): XHead() { }
        XDisjunctiveHead( const std::vector< XAtom >& atoms ): XHead(atoms) { }

    };

    inline
    std::ostream&
    operator<< (
        std::ostream & out,
        const XDisjunctiveHead& h )
    {
        for( unsigned i=0; i<h.atoms.size(); i++ )
        {
            out << h.atoms[i];
            if( i < h.atoms.size()-1 )
                out << " | ";
        }
        out << " ";
        return out;
    }

};};


#endif /* XDISJUNCTIVEHEAD_H */
