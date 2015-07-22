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
 * File:   XParallelRulesetStandard.h
 * Author: pierfrancesco
 *
 * Created on 17 luglio 2015, 18.08
 */

#ifndef XPARALLELRULESETSTANDARD_H
#define XPARALLELRULESETSTANDARD_H

#include "XParallelRuleset.h"

#include "../../util/Assert.h"

namespace DLV2{ namespace REWRITERS{

    class XParallelRulesetStandard : public XParallelRuleset {
    public:
        XParallelRulesetStandard( const XProgram& inputProgram ): XParallelRuleset(inputProgram), it(inputProgram.beginRules()) { }
        virtual ~XParallelRulesetStandard() { }

        virtual bool hasNext() { return it != program.endRules(); }
        virtual const XRule& next() { assert_msg( hasNext(), "No more items" ); return *it++; }
        virtual const size_t size() const { return program.rulesSize(); }
        virtual void reset() { it = program.beginRules(); }

    private:
        XProgram::const_iterator it;

    };

};};

#endif /* XPARALLELRULESETSTANDARD_H */
