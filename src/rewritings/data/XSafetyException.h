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
 * File:   XSafetyException.h
 * Author: pierfrancesco
 *
 * Created on 30 ottobre 2014, 15.44
 */

#ifndef XSAFETYEXCEPTION_H
#define XSAFETYEXCEPTION_H

#include "XRule.h"

namespace DLV2{ namespace REWRITERS{

    class XSafetyException : public std::exception {
    public:
        XSafetyException( const XRule& r ): rule(r) { }
        ~XSafetyException() { }

        virtual const char* what() const throw();

    private:
        const XRule& rule;
    };

};};

#endif /* XSAFETYEXCEPTION_H */
