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
 * File:   XTerm.h
 * Author: pierfrancesco
 *
 * Created on 27 ottobre 2014, 16.49
 */

#ifndef XTERM_H
#define XTERM_H

#include <string>
#include <limits>
#include "../../util/Assert.h"

namespace DLV2{ namespace REWRITERS{

    class XTerm {
    public:
        enum Type{ Variable, Integer, String, Null };

        XTerm( const XTerm& t ): value(t.value), text(t.text), type(t.type) { }
        ~XTerm() { }

        unsigned getValue() const { assert_msg( type == Integer, "Not an integer" ); return value; }
        const std::string& getText() const { assert_msg( type != Integer, "It is an integer" ); return text; }
        Type getType() const { return type; }
        bool isVar() const { return getType() == Variable; }
        bool isStandardVar() const { return getType() == Variable && text.compare("_") != 0;  }
        bool isUnknownVar() const { return getType() == Variable && !text.compare("_"); }
        bool isInt() const { return getType() == Integer; }
        bool isString() const { return getType() == String; }
        bool isConst() const { return getType() == String || getType() == Integer; }
        bool isNull() const { return getType() == Null; }
        bool operator==( const XTerm& term ) const;
        bool operator!=( const XTerm& term ) const;
        XTerm& operator=( const XTerm& term );
        bool operator<( const XTerm& term ) const;
        bool operator<=( const XTerm& term ) const;
        bool operator>( const XTerm& term ) const;
        bool operator>=( const XTerm& term ) const;

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XTerm& );
        friend class XProgram;

        // Only class Program can create Term objects.
        // Integer constructor
        XTerm( int val ): value(val), text(""), type(Integer) { }
        XTerm( Type t, const std::string& txt );
        XTerm( Type t, char* txt );

        int value;
        std::string text;
        Type type;
    };

    inline
    std::ostream&
    operator<< (
        std::ostream& out,
        const XTerm& t )
    {
        if( t.getType() == XTerm::Integer )
            out << t.value;
        else
            out << t.text;
        return out;
    }

    // FIXME: ask giorgio to check it..
    struct XTermHasher
    {

    };

};};

namespace std {

    template <>
    struct hash< DLV2::REWRITERS::XTerm >
    {
        size_t operator()( const DLV2::REWRITERS::XTerm& term ) const
        {
            size_t h = 0;
            switch( term.getType() )
            {
            case DLV2::REWRITERS::XTerm::Variable:
                std::hash< std::string > strHash;
                h = strHash(term.getText());
                break;
            case DLV2::REWRITERS::XTerm::Integer:
                h = std::numeric_limits< size_t >::max()-term.getValue();
                break;
            case DLV2::REWRITERS::XTerm::String:
                h = strHash(term.getText());
                break;
            case DLV2::REWRITERS::XTerm::Null:
                h = strHash(term.getText());
                break;
            default:
                assert(0);
            }
            return h;
        }
    };

};


#endif /* XTERM_H */
