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
 * File:   Term.h
 * Author: cesco
 *
 * Created on 28 febbraio 2014, 11.29
 */

#ifndef TERM_H
#define TERM_H

#include <iostream>
#include "Names.h"

namespace DLV2
{
    
    class Term {
    public:
        enum Type{ Variable, Integer, String };

        // Integer constructor
        Term( unsigned );
        // String constructor
        Term( std::string );
        // Variable construtor
        Term( unsigned, std::string );
        // Copy constructor
        Term( const Term& t );
        ~Term() { }

        Type getType() const { return type; }
        unsigned getIndex() const { return index; }

    protected:
        friend inline std::ostream& operator<< ( std::ostream&, const Term& );

        unsigned index;
        std::string varName;
        Type type;
    };

    inline 
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const Term& t )
    {
        if( t.getType() == Term::Integer )
            out << Names::getIntegerConstant(t.index);
        else if( t.getType() == Term::String )
            out << Names::getStringConstant(t.index);
        else
            out << t.varName;
        return out;

    }
    
};

#endif	/* TERM_H */

