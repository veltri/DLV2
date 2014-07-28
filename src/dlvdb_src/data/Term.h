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

namespace DLV2 { namespace DB{

    class Term {
    public:
        Term( const Term& t ): text(t.text) { }
        ~Term() { }
        
    private:
        friend inline std::ostream& operator<< ( std::ostream&, const Term& );
        
        // Only class Program can create Term objects.
        Term() { }
        Term( const std::string& txt ): text(txt) { }
        //friend class Program;
        
        std::string text;        
    };
    
    inline 
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const Term& t )
    {
        out << t.text;
        return out;
    }
    
};};

#endif	/* TERM_H */

