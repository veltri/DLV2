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
 * File:   DBTerm.h
 * Author: pierfrancesco
 *
 * Created on 28 luglio 2014, 18.04
 */

#ifndef DBTERM_H
#define	DBTERM_H

#include <string>
#include "../../util/Assert.h"

namespace DLV2{ namespace DB{

    class DBTerm {
    public:
        enum Type{ Variable, Integer, String };
        
        DBTerm( const DBTerm& t ): value(t.value), text(t.text), type(t.type) { }
        ~DBTerm() { }
        
        unsigned getValue() const { assert_msg( type == Integer, "Not an integer" ); return value; }
        const std::string& getText() const { assert_msg( type != Integer, "It is an integer" ); return text; }
        Type getType() const { return type; }
        bool isVar() const { return getType() == Variable; }
        bool isUnknownVar() const { return getType() == Variable && !text.compare("_"); }
        bool isInt() const { return getType() == Integer; }
        bool isConst() const { return getType() == String; }
        bool operator==( const DBTerm& term ) const;
        
    private:
        friend inline std::ostream& operator<< ( std::ostream&, const DBTerm& );
        friend class DBProgram;
        
        // Only class Program can create Term objects.
        // Integer constructor
        DBTerm( int val ): value(val), text(""), type(Integer) { }
        // String constructor
        DBTerm( const std::string& txt ): text(txt), type(String) { }
        DBTerm( char* txt ): text(txt), type(String) { }
        // Variable constructor; the first parameter allows
        // to distinguish this constructor from the one for strings
        DBTerm( unsigned, const std::string& var ): text(var), type(Variable) { }
        DBTerm( unsigned, char* var ): text(var), type(Variable) { }
        
        int value;
        std::string text;
        Type type;        
    };
    
    inline 
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const DBTerm& t )
    {
        if( t.getType() == DBTerm::Integer )
            out << t.value;
        else
            out << t.text;
        return out;
    }
    
};};

#endif	/* TERM_H */

