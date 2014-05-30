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
 * File:   Directive.h
 * Author: cesco
 *
 * Created on 29 maggio 2014, 23.10
 */

#ifndef DIRECTIVE_H
#define	DIRECTIVE_H

namespace DLV2
{
    // FIXME
    class Directive {
    public:
        Directive( char* n, char* v ): name(n), value(v) { }
        virtual ~Directive() { }
    private:
        friend inline std::ostream& operator<< ( std::ostream&, const Directive& );
        
        std::string name;
        std::string value;
    };
    
    inline 
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const Directive& d )
    {
        out << d.name << d.value;
        return out;
    }
    
};

#endif	/* DIRECTIVE_H */

