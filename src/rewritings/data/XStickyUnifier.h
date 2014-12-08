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
 * File:   XStickyUnifier.h
 * Author: pierfrancesco
 *
 * Created on 04/nov/2014, 19.04
 */

#ifndef XSTICKYUNIFIER_H
#define XSTICKYUNIFIER_H

#include <unordered_map>
#include "../data/XLiteral.h"
#include "XIterableMap.h"

namespace DLV2{ namespace REWRITERS{

    class XStickyUnifier {
    public:
        XStickyUnifier( const XStickyUnifier& unifier );
        ~XStickyUnifier() { }

        const XAtom& getBodyAtom() const { return bodyAtom; }
        const XAtom& getHeadAtom() const { return headAtom; }
        const XMapping& getSubstitution() const { return substitution; }

    private:
        friend class XProgram;

        XStickyUnifier( const XAtom& headAt, const XAtom& bodyAt, const XMapping& subst );

        XAtom headAtom;
        XAtom bodyAtom;
        XMapping substitution;
    };

};};


#endif /* XSTICKYUNIFIER_H */
