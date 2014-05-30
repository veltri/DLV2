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
 * File:   DirectiveFactory.h
 * Author: cesco
 *
 * Created on 29 maggio 2014, 22.58
 */

#ifndef DIRECTIVEFACTORY_H
#define	DIRECTIVEFACTORY_H

#include "Directive.h"

namespace DLV2
{
    
    // FIXME
    class DirectiveFactory {
    public:
        static Directive* createDirective( char* dirName, char* dirValue ) { return new Directive(dirName,dirValue); }
        
    private:
        DirectiveFactory() { }
        DirectiveFactory(const DirectiveFactory&) { }
        ~DirectiveFactory() { }
        
    };
    
};

#endif	/* DIRECTIVEFACTORY_H */

