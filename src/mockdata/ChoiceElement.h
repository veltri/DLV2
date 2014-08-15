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
 * File:   ChoiceElement.h
 * Author: cesco
 *
 * Created on 28 marzo 2014, 18.58
 */

#ifndef CHOICEELEMENT_H
#define	CHOICEELEMENT_H

#include <vector>
#include "Literal.h"

namespace DLV2{ namespace MOCK{

    class ChoiceElement {
    public:
        ChoiceElement( const Atom& a, std::vector<Literal> lits ): at(a), literals(lits) { }
        ChoiceElement( const ChoiceElement& ce ): at(ce.at), literals(ce.literals) { }
        ~ChoiceElement() { }

        void addLiteral( const Literal& l ) { literals.push_back(l); }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const ChoiceElement& );

        Atom at;
        std::vector<Literal> literals;
    };

    inline 
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const ChoiceElement& ce )
    {
        out << ce.at;
        if( ce.literals.size() > 0 )
            out << ":";
        for( unsigned i=0; i<ce.literals.size(); i++ )
        {
            out << ce.literals[i];
            if( i < ce.literals.size()-1 )
                out << ",";
        }
        return out;
    }

};};

#endif	/* CHOICEELEMENT_H */

