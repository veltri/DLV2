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
 * File:   XRulePointersCollection.h
 * Author: pierfrancesco
 *
 * Created on 31 ottobre 2014, 13.45
 */

#ifndef XRULEPOINTERSCOLLECTION_H
#define XRULEPOINTERSCOLLECTION_H

#include "XRandomAccessSet.h"

namespace DLV2{ namespace REWRITERS{

    class XRulePointersCollection {
    public:
        XRulePointersCollection( const XRulePointersCollection& indColl ): indices(indColl.indices) { }
        ~XRulePointersCollection() { }

        size_t size() const { return indices.size(); }
        XRule::const_iterator operator[]( index_t pos ) const { return indices[pos]; }
        XRule::const_iterator at( index_t pos ) const { return indices.at(pos); }
        bool pushRulePointer( XRule::const_iterator ruleIt ) { return indices.pushItem(ruleIt); }
        bool popRulePointer() { return indices.popItem(); }
        bool insertRulePointer( index_t pos, XRule::const_iterator ruleIt ) { return indices.insertItem(pos,ruleIt); }
        bool removeRulePointer( index_t pos ) { return indices.removeItem(pos); }
        bool find( XRule::const_iterator ruleIt ) const { return indices.find(ruleIt); }
        void clear() { indices.clear(); }

    private:
        friend class XProgram;

        XRulePointersCollection(): indices() { }
        XRulePointersCollection( const XRandomAccessSet< XRule::const_iterator >& inds ): indices(inds) { }

        XRandomAccessSet< XRule::const_iterator > indices;
    };

};};

#endif /* XRULEPOINTERSCOLLECTION_H */
