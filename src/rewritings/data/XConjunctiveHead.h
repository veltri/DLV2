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
 * File:   XConjunctiveHead.h
 * Author: pierfrancesco
 *
 * Created on 28 ottobre 2014, 16.44
 */

#ifndef XCONJUNCTIVEHEAD_H
#define XCONJUNCTIVEHEAD_H

#include "XHead.h"

namespace DLV2{ namespace REWRITERS{

    class XConjunctiveHead: public XHead {
    public:
        XConjunctiveHead( const XConjunctiveHead& head ): XHead(head) { }
        virtual ~XConjunctiveHead() { }

        virtual bool isAtomic() const { return false; }
        virtual bool isDisjunctive() const { return false; }
        virtual bool isConjunctive() const { return true; }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XConjunctiveHead& );
        friend class XProgram;

        XConjunctiveHead(): XHead() { }
        XConjunctiveHead( const std::vector< XAtom >& atoms ): XHead(atoms) { }

    };

    inline
    std::ostream&
    operator<< (
        std::ostream & out,
        const XConjunctiveHead& h )
    {
        for( unsigned i=0; i<h.atoms.size(); i++ )
        {
            out << h.atoms[i];
            if( i < h.atoms.size()-1 )
                out << " ^ ";
        }
        out << " ";
        return out;
    }

};};


#endif /* XCONJUNCTIVEHEAD_H */
