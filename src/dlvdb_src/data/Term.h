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
 * Author: pierfrancesco
 *
 * Created on 28 luglio 2014, 18.04
 */

#ifndef TERM_H
#define	TERM_H

#include <string>

namespace DLV2 { namespace DB{

    class Term {
    public:
        enum Type{ Variable, Integer, String };
        
        Term( const Term& t ): value(t.value), text(t.text), type(t.type) { }
        ~Term() { }
        
        unsigned getValue() const { return value; }
        const std::string& getText() const { return text; }
        Type getType() const { return type; }
        
    private:
        friend inline std::ostream& operator<< ( std::ostream&, const Term& );
        friend class Program;
        
        // Only class Program can create Term objects.
        Term() { }
        // Integer constructor
        Term( unsigned val ): value(val), text(""), type(Integer) { }
        // String constructor
        Term( const std::string& txt ): text(txt), type(String) { }
        // Variable constructor; the first parameter allows
        // to distinguish this constructor from the one for strings
        Term( unsigned, const std::string& var ): text(var), type(Variable) { }
        
        unsigned value;
        std::string text;
        Type type;        
    };
    
    inline 
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const Term& t )
    {
        if( t.getType() == Term::Integer )
            out << t.value;
        else
            out << t.text;
        return out;
    }
    
};};

#endif	/* TERM_H */

