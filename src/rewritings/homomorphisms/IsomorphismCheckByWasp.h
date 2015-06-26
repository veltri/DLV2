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
 * File:   IsomorphismCheckByWasp.h
 * Author: pierfrancesco
 *
 * Created on 14 novembre 2014, 16.03
 */

#ifndef ISOMORPHISMCHECKBYWASP_H
#define ISOMORPHISMCHECKBYWASP_H

#include <string>
#include "IsomorphismCheckStrategy.h"
#include "../data/XRenamingCache.h"
#include "../data/XMGUCache.h"

namespace DLV2{ namespace REWRITERS{

    class IsomorphismCheckByWasp: public IsomorphismCheckStrategy {
    public:
        IsomorphismCheckByWasp( const XProgram& p ): IsomorphismCheckStrategy(p), renamingCache(), mguCache() { }
        virtual ~IsomorphismCheckByWasp() { }

        /** Check whether there exists an isomorphism between rules 'ruleRightSide' and
         * 'ruleLeftSide'.
         * @return Whether such a condition holds and the eventual isomorphism, h, computed,
         * where h is defined as h: dom(ruleRightSide) --> dom(ruleLeftSide)
         */
        virtual std::pair< XMapping*, bool > areIsomorphic(
                const XRule& ruleLeftSide,
                const XRule& ruleRightSide );
        /** Check whether there exists an homomorphism from a set of atoms, 'atomRightSide',
         * to another set of atoms, 'atomsLeftSide'. We remind that such a condition holds
         * if there exists an homomorphism h: dom(atomsRightSide) --> dom(atomsLeftSide)
         * such that atomsLeftSide = h(atomsRightSide).
         * @return whether such a condition holds and the eventual homomorphism computed
         */
        virtual std::pair< XMapping*, bool > isHomomorphicTo(
                const std::vector< XAtom >& atomsLeftSide,
                const std::vector< XAtom >& atomsRightSide );
        /** Check whether these two sets of atoms are unifiable. Notice that 'atoms1' is
         * assumed to be part of 'rule1'. The same holds for 'atoms1' and 'rule2'.
         * @return Whether such a condition holds and the eventual MGU computed.
         * P.S. To avoid undesirable clutter among variable names, variables from the second
         * atom set have been renamed. Thus, the returned renaming is suitable just for the first
         * atom set.
         */
        virtual std::pair< const XMapping*, bool > areUnifiable(
                const std::vector< XAtom >& atoms1,
                const XRule& rule1,
                const std::vector< XAtom >& atoms2,
                const XRule& rule2 );

    private:
        /** Unify, if possible, 's' and 't' and update 'substitution'.
         * @param s A generic term
         * @param t A generic term
         * @param substitution The mapping under construction
         * @return True if 's' and 't' are unifiable, false otherwise.
         */
        bool unify( const XTerm& s, const XTerm& t, XMapping& substitution ) const;
        /** Compute all the (or just the first) eventual homomorphisms from an
         * atom set A2 to another atom set A1.
         * @param atomsLeftSide The first atom set (A1)
         * @param atomsRightSide The second atom set (A2)
         * @param onlyFirst This flag says whether the caller is interested in the
         * first homomorphism or in all of them
         * @return A (possibly empty) list of homomorphisms. The caller has to take
         * care of destroying such homomorphisms
         */
        std::vector< XMapping* > computeHomomorphisms(
                const std::vector< XAtom >& atomsLeftSide,
                const std::vector< XAtom >& atomsRightSide,
                bool onlyFirst ) const;
        /** Parse the model returned by wasp in order to extract the homomorphisms
         * given by eventual atoms of the query predicate which belong to the model.
         * @param termsMapped the term set containing variables to be mapped
         * @param outputBuffer the string containing the output from wasp
         * @param outputBufferSize the maximum size of the previous buffer
         * @param onlyFirst this flag says whether the caller is interested in
         * all the eventual homomorphism or just in the first one
         * @return If there are no atoms of the query predicate in the model,
         * an empty vector is returned. Otherwise, if the parameter 'onlyFirst'
         * is true, only the first homomorphism extracted is returned;
         * else, it returns a complete list of all the homomorphisms found.
         */
        std::vector< XMapping* > extractMappings(
                const std::vector< XTerm >& termsMapped,
                char outputBuffer[],
                size_t outputBufferSize,
                bool onlyFirst ) const;
        /** Invert the homomorphism 'h' in input and check whether 'h^-1(atoms1) == atoms2'
         * @param h the homomorphism to be checked
         * @param atoms1 the first atom set
         * @param atoms2 the second atom set
         * @return true if h is invertible
         */
        bool isInvertible(
                const XMapping& h,
                const std::vector< XAtom >& atoms1,
                const std::vector< XAtom >& atoms2 ) const;
        /** Invert the homomorphism 'h' in input and check whether 'h^-1(atoms2) == atoms1'
         * @param h the homomorphism to be checked
         * @param atoms1 the first atom set
         * @param atoms2 the second atom set
         * @return true if h is invertible
         */
        bool isExtensibleToHead(
                XMapping& homomorphism,
                const XRule& rule1,
                const XRule& rule2 ) const;
        /** Check whether 'h(atoms2) == atoms1'
         * @param h an homomorphism
         * @param atoms1 the first atom set
         * @param atoms2 the second atom set
         * @return true if such a condition holds
         */
        bool isEquivalentTo(
                const XMapping& h,
                const std::vector< XAtom >& atoms1,
                const std::vector< XAtom >& atoms2 ) const;
        /** Rename the input atom sets and returns a mapping to invert the renaming.
         * @param inputAtoms1 the first atom set to be renamed
         * @param renamedAtoms1 the first atom set is renamed and returned as output
         * @param inputAtoms2 the second atom set to be renamed
         * @param renamedAtoms2 the second atom set is renamed and returned as output
         * @return a mapping to invert the renaming;
         */
        std::pair< const XMapping&, const XRule& > renameInput(
                const XRule& rule );
        /** Rename the input rule and generate a renamed version of the input atom set,
         * @param rule The rule to be renamed
         * @param atoms the atom set is renamed and returned as output
         * @return The renamed atom set and a mapping to invert the renaming,
         * the caller has to take care of destroying such objects;
         */
        std::pair< const XMapping&, std::vector< XAtom >* > renameInput(
                const XRule& rule,
                const std::vector< XAtom >& atoms );
        /** The final mapping computed by the algorithm is expressed
         * in terms of renamed variables. This function inverts such
         * variables given the inverted renaming.
         * @param output the mapping to be renamed
         * @param inverseRenaming the inverse renaming
         * @return the inverted mapping, the caller has to take care of
         * destroying such a mapping;
         */
        XMapping* unrenameOutput(
                const XMapping* output,
                const XMapping* inverseRenaming ) const;

        XRenamingCache renamingCache;
        XMGUCache mguCache;
    };

};};


#endif /* ISOMORPHISMCHECKBYWASP_H */
