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
 * File:   StickyJoinCheckingStrategy.h
 * Author: pierfrancesco
 *
 * Created on 04 novembre 2014, 13.51
 */

#ifndef STICKYJOINCHECKINGSTRATEGY_H
#define STICKYJOINCHECKINGSTRATEGY_H

#include "../data/XStickyExpandedRule.h"
#include "../data/XStickyUnifier.h"
#include "../../util/Constants.h"
#include "InputClassCheckingStrategy.h"
#include "../homomorphisms/IsomorphismCheckByWasp.h"
#include <vector>

namespace DLV2{ namespace REWRITERS{

    class StickyJoinCheckingStrategy: public InputClassCheckingStrategy {
    public:
        StickyJoinCheckingStrategy( const XProgram& p );
        virtual ~StickyJoinCheckingStrategy() { delete isomorphismStrategy; }

        virtual bool check();

    private:
        /** The behavior of this function is described in paper 'Query answering under non-guarded
         * rules in Datalog+/-'; given an input program it returns the set of its expanded rules.
         */
        void TGDExpansion( std::vector< XStickyExpandedRule >& expandedRules );
        /** Check whether 'rule1' is applicable to 'rule2' due to atoms 'atom1' \in head(rule1) and
         * 'atom2' \in body(rule2), if it is then return their MGU.
         * @return The MGU between 'rule1' and 'rule2', and a boolean flag which is true whether
         * the two input rules are unifiable, false otherwise.
         */
        std::pair< XStickyUnifier*, bool > isApplicable(
                const XRule& rule1,
                const XAtom& atom1,
                const XRule& rule2,
                const XAtom& atom2 ) const;
        /** Generate an extra rule according to the algorithm TGDExpansion described in paper
         * 'Query answering under non-guarded rules in Datalog+/-'. Roughly speaking, 'original'
         * is a TGD applicable to 'expanded' due to the atoms 'a' \in head(original) and
         * 'b' \in body(expanded). This function returns the TGD \teta(body(original)) --> \teta(a)
         * where \teta is the substitution associated to the most general unifier, mgu,
         * between 'original' and 'expanded'.
         * @return The extra rule generated
         */
        XRule* generateExtraRule(
                const XRule& original,
                const XRule& expanded,
                const XStickyUnifier& mgu );
        /** This function checks whether a TGD \sigma, homomorphic to 'rule', exists.
         * @return The index of a TGD \sigma \in expandedRule which is homomorphic to 'rule',
         * and a boolean variable which is true whether such a TGD exists, false if it does not.
         */
        std::pair< XRuleIndex, bool > findIsomorphicTGD(
                const XRule& rule,
                std::vector< XStickyExpandedRule >& expandedRules ) const;
        /** The behavior of this function is described in paper 'Query answering under non-guarded
         * rules in Datalog+/-'; given a set of expanded rules it marks the variables according
         * to the procedure described in the paper.
         */
        void SJMarking( std::vector< XStickyExpandedRule >& expandedRules ) const;
        /** The input program is sticky-join iff for each TGD \sigma, in the set of its
         * of expanded rules, there is no marked variable in body(\sigma) that is in a join.
         * @return True if the input program is sticky join, false otherwise.
         */
        bool isStickyJoin( std::vector< XStickyExpandedRule >& expandedRules ) const;

        IsomorphismCheckStrategy* isomorphismStrategy;
        unsigned varsCounter;
    };

};};


#endif /* STICKYJOINCHECKINGSTRATEGY_H */
