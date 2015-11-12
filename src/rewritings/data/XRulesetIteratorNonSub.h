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
 * File:   XRulesetIteratorNonSub.h
 * Author: pierfrancesco
 *
 * Created on 17 luglio 2015, 18.19
 */

#ifndef XRULESETITERATORNONSUB_H
#define XRULESETITERATORNONSUB_H

#include "../../util/Assert.h"
#include "XRulesetIterator.h"
#include "../../util/Trace.h"
#include "../../util/Options.h"

using std::cerr;

namespace DLV2{ namespace REWRITERS{

    class XRulesetIteratorNonSub : public XRulesetIterator {
    public:
        XRulesetIteratorNonSub( const XProgram& inputProgram ): XRulesetIterator(inputProgram), iterators(), it(inputProgram.beginRules()) { }
        XRulesetIteratorNonSub( const XRulesetIteratorNonSub& ruleset ): XRulesetIterator(ruleset.program), iterators(ruleset.iterators), it(program.beginRules()) { }
        virtual ~XRulesetIteratorNonSub() { }

        virtual void pushIterator( XProgram::const_iterator it ) { assert_msg( it != program.endRules(), "Iterator not valid" ); iterators.insert(it); }
        virtual bool hasNext() { while( it != program.endRules() && iterators.find(it) != iterators.end() ) it++; return it != program.endRules(); }
        virtual const XRule& next() { assert_msg( hasNext(), "No more items" ); while( it != program.endRules() && iterators.find(it) != iterators.end() ) it++; return *it++; }
        virtual const size_t size() const { return program.rulesSize() - iterators.size(); }
        virtual void reset() { it = program.beginRules(); }

    private:
        std::unordered_set< XProgram::const_iterator > iterators;
        XProgram::const_iterator it;
    };

};};


#endif /* XRULESETITERATORNONSUB_H */
