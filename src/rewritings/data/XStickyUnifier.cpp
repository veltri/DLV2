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
 * File:   XStickyUnifier.cpp
 * Author: pierfrancesco
 *
 * Created on 04 novembre 2014, 19.12
 */

#include "XStickyUnifier.h"

using namespace DLV2::REWRITERS;

XStickyUnifier::XStickyUnifier(
    const XStickyUnifier& unifier ):
        headAtom(unifier.headAtom),
        bodyAtom(unifier.bodyAtom),
        substitution(unifier.substitution)
{
}

XStickyUnifier::XStickyUnifier(
    const XAtom& headAt,
    const XAtom& bodyAt,
    const XMapping& subst ):
        headAtom(headAt),
        bodyAtom(bodyAt),
        substitution(subst)
{
}
