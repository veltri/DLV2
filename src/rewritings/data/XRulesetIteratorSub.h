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
 * File:   XRulesetIteratorSub.h
 * Author: pierfrancesco
 *
 * Created on 17 luglio 2015, 17.55
 */

#ifndef XRULESETITERATORSUB_H
#define XRULESETITERATORSUB_H

#include "../../util/Assert.h"
#include "XRulesetIterator.h"

namespace DLV2{ namespace REWRITERS{

    class XRulesetIteratorSub : public XRulesetIterator {
    public:
        XRulesetIteratorSub( const XProgram& inputProgram ): XRulesetIterator(inputProgram), iterators(), index(0) { }
        XRulesetIteratorSub( const XRulesetIteratorSub& ruleset ): XRulesetIterator(ruleset.program), iterators(ruleset.iterators), index(0) { }
        virtual ~XRulesetIteratorSub() { }

        virtual void pushIterator( XProgram::const_iterator it ) { assert_msg( it != program.endRules(), "Iterator not valid" ); iterators.push_back(it); }
        virtual bool hasNext() { return index < iterators.size(); }
        virtual const XRule& next() { assert_msg( hasNext(), "No more items" ); return *(iterators[index++]); }
        virtual const size_t size() const { return iterators.size(); }
        virtual void reset() { index = 0; }

    private:
        std::vector< XProgram::const_iterator > iterators;
        unsigned index;

    };

};};

#endif /* XRULESETITERATORSUB_H */
