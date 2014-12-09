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
 * File:   StickyJoinCheckingStrategy.cpp
 * Author: pierfrancesco
 *
 * Created on 04 novembre 2014, 13.57
 */

#include "StickyJoinCheckingStrategy.h"
#include <sstream>

using namespace std;
using namespace DLV2::REWRITERS;

StickyJoinCheckingStrategy::StickyJoinCheckingStrategy(
    const XProgram& p ):
        InputClassCheckingStrategy(p),
        isomorphismStrategy(new IsomorphismCheckByWasp(p)),
        varsCounter(program.getVariablesCounter())
{
}

bool
StickyJoinCheckingStrategy::check()
{
    std::vector< XStickyExpandedRule > expandedRules;
    TGDExpansion(expandedRules);
    SJMarking(expandedRules);
    return isStickyJoin(expandedRules);
}

void
StickyJoinCheckingStrategy::TGDExpansion(
    vector< XStickyExpandedRule >& expandedRules )
{
    // First of all, add each rule of the input program to the
    // expanded rule set as an expanded rule labeled by the /emptyset.
    for( XRule::const_iterator it=program.beginRules(); it!=program.endRules(); it++ )
    {
        const XRule& rule = *it;
        XStickyExpandedRule* expandedRule = program.createStickyExpandedRule(rule);
        expandedRules.push_back(*expandedRule);
        delete expandedRule;
    }

    // Iterate the following process until a fixpoint is reached.
    size_t currMax = expandedRules.size();
    index_t deltaStart = 0;
    while( currMax > deltaStart )
    {
        for( XRule::const_iterator rIt=program.beginRules(); rIt!=program.endRules(); rIt++ )
        {
            for( index_t j=deltaStart; j<currMax; j++ )
            {
                const XRule& originalRule = *rIt;
                const XRule& expandedRule = expandedRules[j].getRule();
                // For each pair of TGDs <originalRule,expandedRule> \in {inputProgram}X{expandedRules},
                // if 'originalRule' is applicable to 'expandedRule' due to the atoms
                // 'a' \in head(originalRule) and 'b' \in body(expandedRule), then let 'extraRule'
                // be the TGD \teta(body(originalRule)) --> \teta(a), where \teta is the substitution
                // associated to the MGU for 'a' and 'b'.
                const XHead* originalHead = originalRule.getHead();
                assert_msg( originalHead != NULL, "Null head" );
                const XBody* expandedBody = expandedRule.getBody();
                if( expandedBody != NULL )
                {
                    for( unsigned x=0; x<originalHead->size(); x++ )
                    {
                        for( unsigned y=0; y<expandedBody->size(); y++ )
                        {
                            pair< XStickyUnifier*, bool > res =
                                    isApplicable(originalRule,originalHead->at(x),expandedRule,expandedBody->at(y).getAtom());

                            if( res.second )
                            {
                                XStickyUnifier* mgu = res.first;
                                assert_msg( mgu != NULL, "Not valid mgu" );
                                XRule* extraRule = NULL;
                                extraRule = generateExtraRule(originalRule,expandedRule,*mgu);
                                // If expandendRules already contains a labeled TGD \sigma'' isomorphic to 'extraRule',
                                // then the pair <expandedRule,b> is added to the label set of \sigma''.
                                assert_msg( extraRule != NULL, "Null generated extra rule" );
                                pair< index_t, bool > iso = findIsomorphicTGD(*extraRule,expandedRules);
                                XStickyLabel* extraLabel = program.createStickyLabel(j,mgu->getBodyAtom());
//                                cout << "adding label: " << *extraLabel << endl;
                                if( iso.second )
                                {
                                    assert_msg( iso.first < expandedRules.size(), "Index out of range" );
                                    expandedRules[iso.first].addLabel(*extraLabel);
//                                    cout << "added to: " << expandedRules[iso.first] << endl;
                                }
                                // Otherwise, the TGD 'extraRule' labeled by {<expandedRule,b>} is added to 'expandedRules'.
                                else
                                {
                                    XStickyExpandedRule* extraExpandedRule = program.createStickyExpandedRule(*extraRule);
                                    extraExpandedRule->addLabel(*extraLabel);
                                    expandedRules.push_back(*extraExpandedRule);
//                                    cout << "added to the new rule: " << *extraExpandedRule << endl;
                                    delete extraExpandedRule;
                                }
                                delete extraLabel;
                                delete extraRule;
                                delete mgu;
                            }
                        }
                    }
                }
            }
        }
        deltaStart = currMax;
        currMax = expandedRules.size();
//        cout << "currMax: " << currMax << "; deltaStart: " << deltaStart << endl;
    }
//    for( index_t i=0; i<expandedRules.size(); i++ )
//        cout << expandedRules[i] << endl;
}

pair< XStickyUnifier*, bool >
StickyJoinCheckingStrategy::isApplicable(
    const XRule& rule1,
    const XAtom& atom1,
    const XRule& rule2,
    const XAtom& atom2 ) const
{
    // Check whether rule1 is applicable to rule2 because of the atoms 'atom1' in head(rule1)
    // and 'atom2' in body(rule2)
    assert_msg( isomorphismStrategy != NULL, "Null strategy" );
    if( atom1.getPredIndex() != atom2.getPredIndex()
            || atom1.getArity() != atom2.getArity() )
        return pair< XStickyUnifier*, bool >(NULL,false);

    vector< XAtom > atoms1;
    atoms1.push_back(atom1);
    vector< XAtom > atoms2;
    atoms2.push_back(atom2);
    pair< const XMapping*, bool > res = isomorphismStrategy->areUnifiable(atoms1,rule1,atoms2,rule2);
    if( !res.second )
    {
        assert_msg( res.first == NULL, "Not null mapping" );
        return pair< XStickyUnifier*, bool >(NULL,false);
    }
    else
    {
//        cout << rule1 << " is unifiable to " << rule2 << " by means of the head atom " << atom1 << " and the body atom " << atom2 << endl;
        assert_msg( res.first != NULL, "Null mapping" );
        assert_msg( atom1.getArity() == atom2.getArity(), "These atoms should not have been unified" );
        typedef vector< unsigned > Positions;
        XIterableMap< XTerm, Positions > termsPositions;
        for( unsigned i=0; i<atom2.getTerms().size(); i++ )
        {
            if( atom2.getTerms().at(i).isConst() )
            {
                if( rule1.isExistential(atom1.getTerms().at(i)) )
                {
                    return pair< XStickyUnifier*, bool >(NULL,false);
                }
            }
            else if( atom2.getTerms().at(i).isStandardVar() )
            {
                XIterableMap< XTerm, Positions >::iterator it = termsPositions.find(atom2.getTerms().at(i));
                if( it == termsPositions.end() )
                {
                    Positions pos;
                    pos.push_back(i);
                    termsPositions.insert(pair< const XTerm&, const Positions& >(atom2.getTerms().at(i),pos));
                }
                else
                    it->second.push_back(i);
            }
        }
        for( unsigned i=0; i<termsPositions.size(); i++ )
        {
            XIterableMap< XTerm, Positions >::const_iterator it = termsPositions[i];
            if( it->second.size() > 1 )
            {
                // If the variable in the first position of 'atom1' is
                // existential, it should appear in every position. Otherwise,
                // no existential variables and constants are allowed.
                bool existentialFirst = rule1.isExistential(atom1.getTerms().at(it->second.at(0)));
                for( unsigned j=0; j<it->second.size(); j++ )
                {
                    unsigned pos = it->second.at(j);
                    assert_msg( pos < atom1.getTerms().size(), "Index out of range" );
                    assert_msg( !atom1.getTerms().at(pos).isNull(), "Null value" );

                    if( existentialFirst )
                    {
                        if( atom1.getTerms().at(pos) != atom1.getTerms().at(0) )
                        {
                            return pair< XStickyUnifier*, bool >(NULL,false);
                        }
                    }
                    else
                    {
                        if( rule1.isExistential(atom1.getTerms().at(pos)) || atom1.getTerms().at(pos).isConst() )
                        {
                            return pair< XStickyUnifier*, bool >(NULL,false);
                        }
                    }
                }
            }
        }
        // If they have passed all the checks they are applicable.
        XStickyUnifier* unifier = program.createStickyUnifier(atom1,atom2,*res.first);
//        cout << "Ok unified" << endl;
        return pair< XStickyUnifier*, bool >(unifier,true);
    }
}

XRule*
StickyJoinCheckingStrategy::generateExtraRule(
    const XRule& original,
    const XRule& expanded,
    const XStickyUnifier& mgu )
{
    const XMapping& mguSubstitution = mgu.getSubstitution();
    unordered_map< string, XTerm > newRuleRenaming;
    // Create the new head.
    const XAtom& originalHeadAtom = mgu.getHeadAtom();
    vector< XTerm > extraHeadTerms;
    for( unsigned j=0; j<originalHeadAtom.getTerms().size(); j++ )
    {
        XMapping::const_iterator res = mguSubstitution.find(originalHeadAtom.getTerms().at(j));
        assert_msg( res != mguSubstitution.end(), "Every head variable/constant should be mapped by MGU" );
        if( res->second.isStandardVar() )
        {
            //Every variable shall be renamed in order to avoid clutter among variable names.
            unordered_map< string, XTerm >::const_iterator itRenaming = newRuleRenaming.find(res->second.getText());
            if( itRenaming == newRuleRenaming.end() )
            {
                stringstream ss;
                ss << "X" << varsCounter++;
                XTerm* extraTerm = program.createStandardVariable(ss.str());
                newRuleRenaming.insert(pair< const string&, const XTerm& >(res->second.getText(),*extraTerm));
                extraHeadTerms.push_back(*extraTerm);
                delete extraTerm;
            }
            else
                extraHeadTerms.push_back(itRenaming->second);
        }
        else
        {
            assert_msg( originalHeadAtom.getTerms().at(j).isConst(), "Unknown variables and nulls are not allowed here." );
            assert_msg( ( originalHeadAtom.getTerms().at(j) == res->second ),
                    "The range of MGU can only be composed by constants and variables" );
            extraHeadTerms.push_back(res->second);
        }
    }
    XAtom* extraHeadAtom = program.createAtom(originalHeadAtom.getPredIndex(),extraHeadTerms);
    XHead* extraHead = program.createAtomicHead(*extraHeadAtom);
    delete extraHeadAtom;

    // Create the new body.
    XBody* extraBody = NULL;
    const XBody* originalBody = original.getBody();
    if( originalBody != NULL )
    {
        XRandomAccessSet< XLiteral > extraBodyLits;
        for( unsigned i=0; i<originalBody->size(); i++ )
        {
            const XAtom& originalBodyAtom = originalBody->at(i).getAtom();
            vector< XTerm > extraBodyTerms;
            for( unsigned j=0; j<originalBodyAtom.getTerms().size(); j++ )
            {
                // Some variables might be unmapped by MGU.
                XMapping::const_iterator res = mguSubstitution.find(originalBodyAtom.getTerms().at(j));
                const XTerm* term = NULL;
                if( res != mguSubstitution.end() )
                    term = &(res->second);
                else
                    term = &(originalBodyAtom.getTerms().at(j));

                if( term->isStandardVar() )
                {
                    //Every variable shall be renamed in order to avoid clutter among variable names.
                    unordered_map< string, XTerm >::const_iterator itRenaming = newRuleRenaming.find(term->getText());
                    if( itRenaming == newRuleRenaming.end() )
                    {
                        stringstream ss;
                        ss << "X" << varsCounter++;
                        XTerm* extraTerm = program.createStandardVariable(ss.str());
                        newRuleRenaming.insert(pair< const string&, const XTerm& >(term->getText(),*extraTerm));
                        extraBodyTerms.push_back(*extraTerm);
                        delete extraTerm;
                    }
                    else
                        extraBodyTerms.push_back(itRenaming->second);
                }
                else
                {
                    assert_msg( originalBodyAtom.getTerms().at(j).isConst(), "Just constants and variables are allowed here." );
                    extraBodyTerms.push_back(res->second);
                }
            }
            // Add an extra atom with the mapped terms just created.
            XAtom* extraBodyAtom = program.createAtom(originalBodyAtom.getPredIndex(),extraBodyTerms);
            XLiteral* extraBodyLiteral = program.createLiteral(*extraBodyAtom,originalBody->at(i).isNaf());
            extraBodyLits.pushItem(*extraBodyLiteral);
            delete extraBodyLiteral;
            delete extraBodyAtom;
        }
        extraBody = program.createBody(extraBodyLits);
    }

    // Create the new rule.
    XRule* extraRule = program.createRule(extraHead,extraBody);

    return extraRule;
}

pair< index_t, bool >
StickyJoinCheckingStrategy::findIsomorphicTGD(
    const XRule& rule,
    vector< XStickyExpandedRule >& expandedRules ) const
{
    for( index_t i=0; i<expandedRules.size(); i++ )
    {
        pair< XMapping*, bool > resIso = isomorphismStrategy->areIsomorphic(rule,expandedRules[i].getRule());
        if (resIso.second )
        {
            assert_msg( resIso.first != NULL, "Null isomorphism" );
            delete resIso.first;
            return pair< index_t, bool >(i,true);
        }
    }
    return pair< index_t, bool >(expandedRules.size(),false);
}

void
StickyJoinCheckingStrategy::SJMarking(
    vector< XStickyExpandedRule >& expandedRules ) const
{
    // For each 'rule' \in 'expandedRules' and for each variable
    // 'term' \in body(rule), if there exists an atom 'a' \in head(rule)
    // such that 'term' doesn't appear in 'a', the each occurrence of
    // 'term' in body(rule) is marked.
    for( index_t i=0; i<expandedRules.size(); i++ )
    {
        assert_msg( expandedRules[i].getRule().getHead() != NULL, "Null head" );
        const XBody* body = expandedRules[i].getRule().getBody();
        if( body != NULL )
        {
            for( unsigned j=0; j<body->size(); j++ )
            {
                const XAtom& atom = body->at(j).getAtom();
                for( unsigned k=0; k<atom.getTerms().size(); k++ )
                {
                    const XTerm& term = atom.getTerms().at(k);
                    if( term.isStandardVar() )
                    {
                        // Mark variable 'term' if there exists an head atom 'a'
                        // such that 'term' does not appear in 'a'.
                        if( expandedRules[i].getHeadOccurrences(term) <
                                expandedRules[i].getRule().getHead()->size() )
                            expandedRules[i].markVariable(term);
                    }
                }
            }
        }
    }

    bool fixpoint;
    do
    {
        fixpoint = true;

        for( index_t i=0; i<expandedRules.size(); i++ )
        {
            const XRule& rule = expandedRules[i].getRule();
            const XRandomAccessSet< XStickyLabel >& labels = expandedRules[i].getLabels();

            for( index_t j=0; j<labels.size(); j++ )
            {
                // Every expanded rule with a non-empty label set has an atomic head.
                assert_msg( (rule.getHead() != NULL && rule.getHead()->size() == 1),
                        "Not valid expanded rule" );
                assert_msg( labels[j].getExpandedRuleIndex() < expandedRules.size(), "Not a valid rule in the current label" );
                const XStickyExpandedRule& labelExpandedRule = expandedRules[labels[j].getExpandedRuleIndex()];
                const XAtom& labelAtom = labels[j].getAtom();
                const vector< XTerm >& labelAtomTerms = labelAtom.getTerms();

                // The head of 'rule' should be atomic: this cycle might be unnecessary.
                for( unsigned x=0; x<rule.getHead()->size(); x++ )
                {
                    // The following is an auxiliary set, it'll be used to check
                    // whether a variable has been already seen in the current head atom.
                    unordered_set< XTerm > vars;
                    for( unsigned y=0; y<rule.getHead()->at(x).getTerms().size(); y++ )
                    {
                        const XTerm& term = rule.getHead()->at(x).getTerms().at(y);
                        // Check whether the current variable has been already checked and is a universal variable.
                        pair< typename unordered_set< XTerm >::const_iterator, bool > firstOccurrence = vars.insert(term);
                        if( firstOccurrence.second && !rule.isExistential(term) )
                        {
                            const vector< XStickyCoordinates >& headPositions = expandedRules[i].getHeadPositions(term);
                            bool hasToBeMarked = true;
                            // Each occurrence of 'term' in the body of the current rule must be marked if,
                            // given the set of its head positions 'S', a marked variable occurs at each position
                            // 'p' \in 'S' in the body of labelLiteral.
                            for( unsigned z=0; z<headPositions.size() && hasToBeMarked; z++ )
                            {
                                // Since the head should be atomic, every head position of term should share
                                // the same atom-positions.
                                assert_msg( (headPositions[z].atomPos == headPositions[(z+1)%headPositions.size()].atomPos),
                                        "Not an atomic head" );
                                // Check whether at each position z in labels[j].getLiteral() a marked variable occurs.
                                assert_msg( headPositions[z].termPos < labelAtomTerms.size(),
                                        "Index out of range: the head atom of the current rule should be homomorphic"
                                        "to the literal in the label, thus they should share the same number of terms." );
                                const XTerm& bodyTermToCheck = labelAtomTerms[headPositions[z].termPos];
                                if( !labelExpandedRule.isMarked(bodyTermToCheck) )
                                {
                                    hasToBeMarked = false;
                                }
                            }
                            if( hasToBeMarked && !expandedRules[i].isMarked(term) )
                            {
                                expandedRules[i].markVariable(term);
                                fixpoint = false;
                            }
                        }
                    }
                }
            }
        }
    }while( !fixpoint );
}

bool
StickyJoinCheckingStrategy::isStickyJoin(
    vector< XStickyExpandedRule >& expandedRules ) const
{
    for( index_t i=0; i<expandedRules.size(); i++ )
    {
        const XRule& rule = expandedRules[i].getRule();
        const XBody* body = rule.getBody();
        if( body != NULL )
        {
            for( unsigned j=0; j<body->size(); j++ )
            {
                // The following check could consider a term more than once (because of
                // eventual joins). That does not affect the correctness of the algorithm.
                // Such a version is likely to be more efficient than a version equipped
                // with a control avoiding multiple checks.
                for( unsigned k=0; k<body->at(j).getAtom().getTerms().size(); k++ )
                {
                    const XTerm& termToCheck = body->at(j).getAtom().getTerms().at(k);
                    if( expandedRules[i].isMarked(termToCheck)
                            && expandedRules[i].getBodyOccurrences(termToCheck) > 1 )
                        return false;
                }
            }
        }
    }
    return true;
}
