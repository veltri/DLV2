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
 * File:   XParallelRulesetNonSub.h
 * Author: pierfrancesco
 *
 * Created on 17 luglio 2015, 18.19
 */

#ifndef XPARALLELRULESETNONSUB_H
#define XPARALLELRULESETNONSUB_H

#include "XParallelRuleset.h"

#include "../../util/Assert.h"

namespace DLV2{ namespace REWRITERS{

    class XParallelRulesetNonSub : public XParallelRuleset {
    public:
        XParallelRulesetNonSub( const XProgram& inputProgram ): XParallelRuleset(inputProgram), iterators(), it(inputProgram.beginRules()) { }
        XParallelRulesetNonSub( const XParallelRulesetNonSub& ruleset ): XParallelRuleset(ruleset.program), iterators(ruleset.iterators), it(ruleset.it) { }
        virtual ~XParallelRulesetNonSub() { }

        virtual void dontShow( XProgram::const_iterator it ) { assert_msg( it != program.endRules(), "Iterator not valid" ); iterators.insert(it); }
        virtual bool hasNext() { while( iterators.find(it) != iterators.end() ) it++; return it != program.endRules(); }
        virtual const XRule& next() { assert_msg( hasNext(), "No more items" ); while( iterators.find(it) != iterators.end() ) it++; return *it++; }
        virtual const size_t size() const { return program.rulesSize() - iterators.size(); }
        virtual void reset() { it = program.beginRules(); }

    private:
        std::unordered_set< XProgram::const_iterator > iterators;
        XProgram::const_iterator it;
    };

};};


#endif /* XPARALLELRULESETNONSUB_H */
