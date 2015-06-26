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
 * File:   IsomorphismCheckByWasp.cpp
 * Author: pierfrancesco
 *
 * Created on 14 novembre 2014, 16.06
 */

#include "IsomorphismCheckByWasp.h"

#include "../../util/Assert.h"
#include "../../util/ErrorMessage.h"
#include "../../util/Utils.h"
#include "../../util/Constants.h"
#include "../../util/Trace.h"
#include "../../util/Options.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <sys/types.h>
#include <cstdlib>
#include <sstream>
#include <boost/algorithm/string/case_conv.hpp>
#include <cstring>

using namespace DLV2::REWRITERS;
using namespace std;

pair< XMapping*, bool >
IsomorphismCheckByWasp::areIsomorphic(
    const XRule& rule1,
    const XRule& rule2 )
{
    assert_msg( ( rule1.getHead() != NULL && rule2.getHead() != NULL ), "Null heads" );
    // The following controls avoid some useless isomorphic checks.
    if( rule1.getHead()->size() != rule2.getHead()->size() )
        return pair< XMapping*, bool >(NULL,false);
    if( rule1.getHead()->size() == 1
            && ( rule1.getHead()->at(0).getPredIndex() != rule2.getHead()->at(0).getPredIndex()
                    || rule1.getHead()->at(0).getArity() != rule2.getHead()->at(0).getArity() ) )
        return pair< XMapping*, bool >(NULL,false);
    // Check also the atoms type.
    for( unsigned i=0; i<rule1.getHead()->size(); i++ )
    {
        const XAtomType& atomType1 = rule1.getHead()->at(i).getType();
        if( atomType1 != rule2.getHead()->at(i).getType() )
            return pair< XMapping*, bool >(NULL,false);
        // The arities of the current pair of predicates are the same.
        for( unsigned j=0; j<atomType1.getConstantPositions().size(); j++ )
            if( rule1.getHead()->at(i).getTerms().at(atomType1.getConstantPositions().at(j)) !=
                    rule2.getHead()->at(i).getTerms().at(atomType1.getConstantPositions().at(j)) )
                return pair< XMapping*, bool >(NULL,false);
    }
    if( rule1.getBody() != NULL || rule2.getBody() != NULL )
    {
        if( rule1.getBody() == NULL || rule2.getBody() == NULL )
            return pair< XMapping*, bool >(NULL,false);
        else if( rule1.getBody()->size() != rule2.getBody()->size() )
            return pair< XMapping*, bool >(NULL,false);
        else if( rule1.getBody()->size() == 1
                && ( rule1.getBody()->at(0).getAtom().getPredIndex() != rule2.getBody()->at(0).getAtom().getPredIndex()
                        || rule1.getBody()->at(0).getAtom().getArity() != rule2.getBody()->at(0).getAtom().getArity() ) )
            return pair< XMapping*, bool >(NULL,false);
        // Check also the atoms type.
        for( unsigned i=0; i<rule1.getBody()->size(); i++ )
        {
            const XAtomType& atomType1 = rule1.getBody()->at(i).getAtom().getType();
            if( atomType1 != rule2.getBody()->at(i).getAtom().getType() )
                return pair< XMapping*, bool >(NULL,false);
            // The arities of the current pair of predicates are the same.
            for( unsigned j=0; j<atomType1.getConstantPositions().size(); j++ )
                if( rule1.getBody()->at(i).getAtom().getTerms().at(atomType1.getConstantPositions().at(j)) !=
                        rule2.getBody()->at(i).getAtom().getTerms().at(atomType1.getConstantPositions().at(j)) )
                    return pair< XMapping*, bool >(NULL,false);
        }
    }

    // If no check failed, call WASP in order to check if any isomorphism exists.
    // The renamed rule will be instantiated by function 'renameInput'.
    pair< const XMapping&, const XRule& > renamingResult = renameInput(rule2);
    // REMINDER: don't delete 'renamedRule2' and 'renaming', they come from 'renamingCache'.
//    const XMapping* renaming = renamingResult.first;
    const XRule& renamedRules2 = renamingResult.second;

    pair< XMapping*, bool > result;
    const XBody* body1Ptrs = rule1.getBody();
    const XBody* body2Ptrs = renamedRules2.getBody();
    assert_msg( (( body1Ptrs != NULL && body2Ptrs != NULL ) || ( body1Ptrs == NULL && body2Ptrs == NULL )), "Null bodies" );
    if( body1Ptrs != NULL )
    {
        vector< XAtom > body1Atoms;
        vector< XAtom > body2Atoms;
        for( unsigned i=0; i<body1Ptrs->size(); i++ )
        {
            body1Atoms.push_back(body1Ptrs->at(i).getAtom());
            body2Atoms.push_back(body2Ptrs->at(i).getAtom());
        }
        // Now we are interested in all possible homomorphisms.
        bool onlyFirst = false;
        vector< XMapping* > bodyHomomorphisms = computeHomomorphisms(body1Atoms,body2Atoms,onlyFirst);
        if( bodyHomomorphisms.size() == 0 )
            return pair< XMapping*, bool >(NULL,false);

        // If at least an homomorphism h_i exists and can be inverted in a way such that
        // h_i^-1(body2Atoms) = body1Atom then body1Atoms and body2Atoms are isomorphic.
        // If the bodies are isomorphic, by means of an isomorphism h, try to extend
        // h to the head of the rules. If it is extensible, it is a valid isomorphism
        // for the input rules.
        int indexValidIsomorphism = -1;
        for( unsigned i=0; i<bodyHomomorphisms.size(); i++ )
        {
            assert_msg( bodyHomomorphisms[i] != NULL, "Null homomorphism" );

            if( indexValidIsomorphism == -1
                    && isInvertible(*bodyHomomorphisms[i],body1Atoms,body2Atoms) )
            {
                if( isExtensibleToHead(*bodyHomomorphisms[i],rule1,renamedRules2) )
                {
                    indexValidIsomorphism = i;
                }
            }
            // REMINDER: delete every i^th bodyHomomorphisms which you don't return.
            if( indexValidIsomorphism != (int)i )
                delete bodyHomomorphisms[i];
        }
        if( indexValidIsomorphism != -1 )
        {
//            XMapping* outputMapping = unrenameOutput(bodyHomomorphisms[indexValidIsomorphism],inverseRenaming);
//            delete bodyHomomorphisms[indexValidIsomorphism];
//            result.first = outputMapping;
            result.first = bodyHomomorphisms[indexValidIsomorphism];
            result.second = true;
        }
        else
        {
            result.first = NULL;
            result.second = false;
        }
    }
    else
    {
        const XHead* head1Ptrs = rule1.getHead();
        const XHead* head2Ptrs = renamedRules2.getHead();
        assert_msg( ( head1Ptrs != NULL && head2Ptrs != NULL ), "Null heads" );
        vector< XAtom > head1Atoms;
        vector< XAtom > head2Atoms;
        for( unsigned i=0; i<head1Ptrs->size(); i++ )
        {
            head1Atoms.push_back(head1Ptrs->at(i));
            head2Atoms.push_back(head2Ptrs->at(i));
        }
        // Now we are interested in all possible homomorphisms.
        bool onlyFirst = false;
        vector< XMapping* > headHomomorphisms = computeHomomorphisms(head1Atoms,head2Atoms,onlyFirst);
        if( headHomomorphisms.size() == 0 )
            return pair< XMapping*, bool >(NULL,false);

        // If at least an homomorphism h_i exists and can be inverted in a way such that
        // h_i^-1(head2Atoms) = head1Atom then head1Atoms and head2Atoms are isomorphic.
        // In such a case, since the bodies are null, the input rules are isomorphic
        int indexValidIsomorphism = -1;
        for( unsigned i=0; i<headHomomorphisms.size(); i++ )
        {
            assert_msg( headHomomorphisms[i] != NULL, "Null homomorphism" );

            if( indexValidIsomorphism == -1
                    && isInvertible(*headHomomorphisms[i],head1Atoms,head2Atoms) )
            {
                indexValidIsomorphism = i;
            }
            // REMINDER: delete every i^th bodyHomomorphisms which you don't return.
            if( indexValidIsomorphism != (int)i )
                delete headHomomorphisms[i];
        }
        if( indexValidIsomorphism != -1 )
        {
//            XMapping* outputMapping = unrenameOutput(headHomomorphisms[indexValidIsomorphism],inverseRenaming);
//            delete headHomomorphisms[indexValidIsomorphism];
//            result.first = outputMapping;
            result.first = headHomomorphisms[indexValidIsomorphism];
            result.second = true;
        }
        else
        {
            result.first = NULL;
            result.second = false;
        }
    }
    return result;
}


std::pair< XMapping*, bool >
IsomorphismCheckByWasp::isHomomorphicTo(
    const vector< XAtom >& atomsLeftSide,
    const vector< XAtom >& atomsRightSide )
{
    // If the atom sets do not have the same structure they are not homomorphic.
    if( atomsLeftSide.size() != atomsRightSide.size() )
    {
        return pair< XMapping*, bool >(NULL,false);
    }
    for( unsigned i=0; i<atomsLeftSide.size(); i++ )
    {
        if( atomsLeftSide[i].getPredIndex() != atomsRightSide[i].getPredIndex()
                || atomsLeftSide[i].getArity() != atomsRightSide[i].getArity() )
        {
            return pair< XMapping*, bool >(NULL,false);
        }

        const XAtomType& atomType1 = atomsLeftSide[i].getType();
        const XAtomType& atomType2 = atomsRightSide[i].getType();
        // If the current pair of atoms have two different constants in the same position
        // they can't be homomorphic.
        for( unsigned j=0; j<atomType1.getConstantPositions().size(); j++ )
        {
            if( atomsRightSide[i].getTerms().at(atomType1.getConstantPositions().at(j)).isConst() &&
                    ( atomsLeftSide[i].getTerms().at(atomType1.getConstantPositions().at(j)) !=
                    atomsRightSide[i].getTerms().at(atomType1.getConstantPositions().at(j)) ) )
            {
                return pair< XMapping*, bool >(NULL,false);
            }
        }

        for( unsigned j=0; j<atomType2.getConstantPositions().size(); j++ )
        {
            if( atomsLeftSide[i].getTerms().at(atomType2.getConstantPositions().at(j)).isConst() &&
                    ( atomsLeftSide[i].getTerms().at(atomType2.getConstantPositions().at(j)) !=
                    atomsRightSide[i].getTerms().at(atomType2.getConstantPositions().at(j)) ) )
            {
                return pair< XMapping*, bool >(NULL,false);
            }
        }
    }
//    vector< XAtom > renamedAtoms1;
//    vector< XAtom > renamedAtoms2;
//    XMapping* inverseRenaming = renameInput(atoms1,renamedAtoms1,atoms2,renamedAtoms2);

    // We are looking for an homomorphism. If there are more than one, the first one will be ok.
    bool onlyFirst = true;
    vector< XMapping* > homomorphisms = computeHomomorphisms(atomsLeftSide,atomsRightSide,onlyFirst);
    assert_msg( homomorphisms.size() == 0 || homomorphisms.size() == 1, "Something went wrong" );
    if( homomorphisms.size() == 0 )
        return pair< XMapping*, bool >(NULL,false);

//    XMapping* outputMapping = unrenameOutput(homomorphisms[0],inverseRenaming);
//    delete homomorphisms[0];
//    delete inverseRenaming;
    return pair< XMapping*, bool >(homomorphisms[0],true);
}

pair< const XMapping*, bool >
IsomorphismCheckByWasp::areUnifiable(
    const vector< XAtom >& atoms1,
    const XRule& rule1,
    const vector< XAtom >& atoms2,
    const XRule& rule2 )
{
    XMGUCache::const_iterator cache = mguCache.find(atoms1,atoms2);
    if( cache == mguCache.end() )
    {
        if( atoms1.size() != atoms2.size() )
        {
            // Remember they are not unifiable.
            mguCache.insert(atoms1,atoms2);
            return pair< const XMapping*, bool >(NULL,false);
        }
        for( unsigned i=0; i<atoms1.size(); i++ )
        {
            if( atoms1[i].getPredIndex() != atoms2[i].getPredIndex()
                    || atoms1[i].getArity() != atoms2[i].getArity() )
            {
                // Remember they are not unifiable.
                mguCache.insert(atoms1,atoms2);
                return pair< const XMapping*, bool >(NULL,false);
            }
            const XAtomType& atomType1 = atoms1[i].getType();
            const XAtomType& atomType2 = atoms2[i].getType();
            // If the current pair of atoms have two different constants in the same position
            // they are not unifiable.
            for( unsigned j=0; j<atomType1.getConstantPositions().size(); j++ )
                if( atoms2[i].getTerms().at(atomType1.getConstantPositions().at(j)).isConst() &&
                        ( atoms1[i].getTerms().at(atomType1.getConstantPositions().at(j)) !=
                        atoms2[i].getTerms().at(atomType1.getConstantPositions().at(j)) ) )
                {
                    // Remember they are not unifiable.
                    mguCache.insert(atoms1,atoms2);
                    return pair< const XMapping*, bool >(NULL,false);
                }

            for( unsigned j=0; j<atomType2.getConstantPositions().size(); j++ )
                if( atoms1[i].getTerms().at(atomType2.getConstantPositions().at(j)).isConst() &&
                        ( atoms1[i].getTerms().at(atomType2.getConstantPositions().at(j)) !=
                        atoms2[i].getTerms().at(atomType2.getConstantPositions().at(j)) ) )
                {
                    // Remember they are not unifiable.
                    mguCache.insert(atoms1,atoms2);
                    return pair< const XMapping*, bool >(NULL,false);
                }
        }
        // Rename the variables of the second atom set in order to avoid undesirable clutter.
        pair< const XMapping&, vector< XAtom >* > renamingResult = renameInput(rule2,atoms2);
    //    XMapping* renaming = renamingResult.first;
        // REMINDER: destroy 'renamedAtoms2' before leaving.
        vector< XAtom >* renamedAtoms2 = renamingResult.second;
        // At this point, the input atoms' variables have been renamed.

        // Initialize the substitution to the identity mapping.
        XMapping substitution;
        for( unsigned i=0; i<atoms1.size(); i++ )
            for( unsigned j=0; j<atoms1[i].getTerms().size(); j++ )
                substitution.insert(pair< const XTerm&, const XTerm& >(atoms1[i].getTerms().at(j),atoms1[i].getTerms().at(j)));
        for( unsigned i=0; i<renamedAtoms2->size(); i++ )
            for( unsigned j=0; j<renamedAtoms2->at(i).getTerms().size(); j++ )
                substitution.insert(pair< const XTerm&, const XTerm& >(renamedAtoms2->at(i).getTerms().at(j),renamedAtoms2->at(i).getTerms().at(j)));

        // Assume the atom sets have been already ordered.
        bool ok = true;
        for( unsigned i=0; i<atoms1.size() && ok; i++ )
        {
            for( unsigned j=0; j<atoms1[i].getTerms().size() && ok; j++ )
            {
                XMapping::const_iterator sIt = substitution.find(atoms1[i].getTerms().at(j));
                XMapping::const_iterator tIt = substitution.find(renamedAtoms2->at(i).getTerms().at(j));
                assert_msg( sIt != substitution.end(), "Every term should be mapped" );
                assert_msg( tIt != substitution.end(), "Every term should be mapped" );
                if( !unify(sIt->second,tIt->second,substitution) )
                    ok = false;
            }
        }

        pair< XMapping*, bool > res;
        delete renamedAtoms2;
        if( ok )
        {
            // Don't restore variable names because, otherwise, some conflicts might show up.
            // Ex. Is rule '\sigma: p(X1,a) :- p(b,X1).' applicable to itself?
            XMGUCache::iterator ins = mguCache.insert(atoms1,atoms2,substitution);
            return pair< const XMapping*, bool >(ins->second.getMgu(),true);
        }
        // Remember they are not unifiable.
        mguCache.insert(atoms1,atoms2);
        return pair< const XMapping*, bool >(NULL,false);
    }
    else
    {
        return pair< const XMapping*, bool >(cache->second.getMgu(),cache->second.exists());
    }
}

bool
IsomorphismCheckByWasp::unify(
    const XTerm& s,
    const XTerm& t,
    XMapping& substitution ) const
{
    assert_msg( ( !s.isUnknownVar() && !t.isUnknownVar() ), "Unknown variables not allowed here" );
    if( s.isStandardVar() && s == t )
    {
        return true;
    }
    else if( s.isConst() && t.isConst() )
    {
        if( s == t )
            return true;
        else
            return false;
    }
    else if( s.isConst() )
        return unify(t,s,substitution);

    substitution.substitute(pair< const XTerm&, const XTerm& >(s,t));
    for( unsigned i=0; i<substitution.size(); i++ )
    {
        XMapping::iterator it = substitution.at(i);
        if( it->second == s )
        {
            substitution.substitute(pair< const XTerm&, const XTerm& >(it->first,t));
        }
    }
    return true;
}

vector< XMapping* >
IsomorphismCheckByWasp::computeHomomorphisms(
    const std::vector< XAtom >& atoms1,
    const std::vector< XAtom >& atoms2,
    bool onlyFirst ) const
{
    // Given two sets of atoms, create a database with the first one and a query with
    // the second one. The database is got by means of an isomorphism which maps
    // every constant of the atoms in the first set to a different integer constant
    // (starting from 0) and every variable to a constant represented by its lower-case
    // version. Finally, each ground atom obtained is added to the database.
    // Instead, the query is a rule whose body comes up from the conjunction of the atoms
    // in the second set. In the head of such a query there is just an atom with all the
    // terms appearing in its body.

    // The isomorphism used to instantiate the database will be stored because it will
    // be considered again later. Variables are renamed by their lower-case version
    // while constants are substituted by integers (starting from 0) in order to avoid
    // undesirable clutters between variables and constants.
    XMapping tetaDatabase;
    unsigned currConst = 0;
    stringstream programToBeChecked;
    for( unsigned i=0; i<atoms1.size(); i++ )
    {
        assert_msg( atoms1[i].getPredicateName().size() > 0, "Empty predicate name." );
        // Gringo does not accept predicate names starting with a capital letter.
        programToBeChecked << (char)tolower(atoms1[i].getPredicateName().front())
                << atoms1[i].getPredicateName().substr(1,string::npos) << "(";
        for( unsigned j=0; j<atoms1[i].getTerms().size(); j++ )
        {
            XMapping::iterator it = tetaDatabase.find(atoms1[i].getTerms().at(j));
            if( it == tetaDatabase.end() )
            {
                XTerm* dbTerm = NULL;

                if( atoms1[i].getTerms().at(j).isConst() )
                    dbTerm = program.createIntegerConstant(currConst++);
                else if( atoms1[i].getTerms().at(j).isStandardVar() )
                    dbTerm = program.createStringConstant(boost::to_lower_copy(atoms1[i].getTerms().at(j).getText()));
                else
                    assert_msg( 0, "Nulls and unknown variables are not allowed here" );

                tetaDatabase.insert(pair< const XTerm&, const XTerm& >(atoms1[i].getTerms().at(j),*dbTerm));
                programToBeChecked << (*dbTerm);
                delete dbTerm;
            }
            else
                programToBeChecked << it->second;

            if( j < atoms1[i].getTerms().size()-1 )
                programToBeChecked << ",";
        }
        programToBeChecked << ").\n";
    }

    // REMIND: Query constants must be substituted according to mapping
    // 'tetaDatabase' otherwise eventual matchings might be lost.
    XMapping::const_iterator mapIterator;
    stringstream queryBody;
    vector< XTerm > queryTerms;
    for( unsigned i=0; i<atoms2.size(); i++ )
    {
        assert_msg( atoms2[i].getPredicateName().size() > 0, "Empty predicate name." );
        queryBody << (char)tolower(atoms2[i].getPredicateName().front())
                << atoms2[i].getPredicateName().substr(1,string::npos) << "(";
        for( unsigned j=0; j<atoms2[i].getTerms().size(); j++ )
        {
            if( atoms2[i].getTerms().at(j).isConst() )
            {
                // Rename also these constants in order to avoid undesirable clutters
                // with the (just created) database constants.
                mapIterator = tetaDatabase.find(atoms2[i].getTerms().at(j));
                if( mapIterator == tetaDatabase.end() )
                {
                    XTerm* queryTerm = program.createIntegerConstant(currConst++);
                    pair< XMapping::iterator, bool > res =
                            tetaDatabase.insert(pair< XTerm, XTerm >(atoms2[i].getTerms().at(j),*queryTerm));
                    mapIterator = res.first;
                    delete queryTerm;
                }
                queryBody << mapIterator->second;
                queryTerms.push_back(mapIterator->second);
            }
            else
            {
                queryBody << atoms2[i].getTerms().at(j);
                queryTerms.push_back(atoms2[i].getTerms().at(j));
            }

            if( j < atoms2[i].getTerms().size()-1 )
                queryBody << ",";
        }
        queryBody << ")";
        if( i < atoms2.size()-1 )
            queryBody << ",";
    }
    queryBody << ".\n";

    programToBeChecked << TARGET_PRED << "(";
    for( unsigned i=0; i<queryTerms.size(); i++ )
    {
        programToBeChecked << queryTerms[i];
        if( i < queryTerms.size()-1 )
            programToBeChecked << ",";
    }
    programToBeChecked << ") :- " << queryBody.str();

    trace_msg( rewriting, 4, "Homomorphism check - the input program is: " << programToBeChecked.str() );
    char outputBuffer[BUFFER_MAX_LENGTH];
    // Gringo is used to get a ground version of the input program.
    Utils::systemCallTo("./executables/gringo",programToBeChecked.str(),outputBuffer,BUFFER_MAX_LENGTH);
    // The output of gringo is sent to wasp.
    Utils::systemCallTo("./executables/wasp",string(outputBuffer),outputBuffer,BUFFER_MAX_LENGTH);

    // If the model returned by wasp contains at least an occurrence of TARGET_PRED,
    // then there exists an homomorphism between atom1 and atom2.
    // The homomorphisms should be extracted by parsing the returned model which is stored
    // in outputBuffer.
    vector< XMapping* > tetaList = extractMappings(queryTerms,outputBuffer,BUFFER_MAX_LENGTH,onlyFirst);
    if( tetaList.size() == 0 )
        return tetaList;

    assert_msg( ( !onlyFirst || tetaList.size() == 1 ), "Not valid number of homomorphisms returned" );

    // Anyway, we need to return homomorphisms h_i: dom(atoms2) --> dom(atoms1) s.t.
    // atoms1 = h_i(atoms2). Hence, compute the inverse homomorphism 'tetaDatabase^-1'
    // because 'h_i' = 'tetaDatabase^-1' o 'tetaList_i' for each 0 <= i < tetaList.size();
    // our variable renaming algorithm guarantees that such a substitution is an homomorphism.
    XMapping tetaDatabaseInverse;
    for( unsigned i=0; i<tetaDatabase.size(); i++ )
        tetaDatabaseInverse.insert(pair< const XTerm&, const XTerm& >(tetaDatabase[i]->second,tetaDatabase[i]->first));

    vector< XMapping* > hList;
    for( unsigned i=0; i<tetaList.size(); i++ )
    {
        XMapping* h = new XMapping();
        for( unsigned j=0; j<tetaList[i]->size(); j++ )
        {
            const XTerm* term;
            const XTerm* termImage;
            // Constants have been substituted, therefore they need mapping.
            if( tetaList[i]->at(j)->first.isConst() )
            {
                mapIterator = tetaDatabaseInverse.find(tetaList[i]->at(j)->first);
                assert_msg( mapIterator != tetaDatabaseInverse.end(), "Every constant should have been substituted" );
                term = &mapIterator->second;
            }
            else
            {
                term = &(tetaList[i]->at(j)->first);
            }
            mapIterator = tetaDatabaseInverse.find(tetaList[i]->at(j)->second);
            assert_msg( mapIterator != tetaDatabaseInverse.end(),
                    "Every database term should be mapped by the homomorphism" );
            termImage = &mapIterator->second;

            assert_msg( ( term != NULL && termImage != NULL ), "Something went wrong." );
            h->insert(pair< const XTerm&, const XTerm& >(*term,*termImage));
        }
        delete tetaList[i];
        hList.push_back(h);
    }
    return hList;
}

vector< XMapping* >
IsomorphismCheckByWasp::extractMappings(
    const vector< XTerm >& termsMapped,
    char outputBuffer[],
    size_t outputBufferSize,
    bool onlyFirst ) const
{
    vector< XMapping* > homomorphismPtrs;
    unsigned termCounter = 0;
    // Every model returned by wasp is a set of comma-separated
    // atoms enclosed between braces.
    char* pointer = strchr(outputBuffer,'{');
    char* atomPointer = strtok(pointer,"{}(, ");
    bool parsingTerms = false;
    bool stop = false;
    while( atomPointer != NULL && !stop )
    {
        if( parsingTerms )
        {
            string termString(atomPointer);
            assert_msg( termString != string(TARGET_PRED), "Not valid term name" );
            // Character ')' closes the atom and, thus, also the current homomorphism.
            size_t parPos = termString.find(')');
            if( parPos != string::npos )
            {
                termString.erase(parPos);
                parsingTerms = false;
                if( onlyFirst )
                    stop = true;
            }
            XTerm* term;
            int termInteger;
            if( DLV2::Utils::parseInteger(termString.c_str(),termInteger) )
                term = program.createIntegerConstant(termInteger);
            else
                term = program.createStringConstant(termString);

            assert_msg( term != NULL, "Null term" );
            assert_msg( termCounter < termsMapped.size(), "Not valid mapping" );
            // Don't take care of eventual duplicate variables because wasp
            // maps exactly each variable to one constant term.
            pair< const XTerm&, const XTerm& > mapping(termsMapped[termCounter++],*term);
            homomorphismPtrs.back()->insert(mapping);
            delete term;
        }
        else if( strcmp(atomPointer,TARGET_PRED) == 0 )
        {
            parsingTerms = true;
            XMapping* homomorphism = new XMapping();
            homomorphismPtrs.push_back(homomorphism);
        }
        atomPointer = strtok(NULL,"{}(, ");
    }
    return homomorphismPtrs;
}

bool
IsomorphismCheckByWasp::isInvertible(
    const XMapping& homomorphism,
    const vector< XAtom >& atoms1,
    const vector< XAtom >& atoms2 ) const
{
    XMapping inverse;
    for( index_t i=0; i<homomorphism.size(); i++ )
    {
        // A valid homomorphism maps: i) each element just once, and,
        // ii) each constant to itself.
        if( inverse.find(homomorphism.at(i)->second) != inverse.end() )
            return false;
        if( homomorphism.at(i)->second.isConst()
                && homomorphism.at(i)->second != homomorphism.at(i)->first )
            return false;

        pair< const XTerm&, const XTerm& > inverseSubstitution(homomorphism.at(i)->second,homomorphism.at(i)->first);
        inverse.insert(inverseSubstitution);
    }
    return isEquivalentTo(inverse,atoms2,atoms1);
}

bool
IsomorphismCheckByWasp::isExtensibleToHead(
    XMapping& homomorphism,
    const XRule& rule1,
    const XRule& rule2 ) const
{
    assert_msg( rule1.getHead() != NULL, "Null head1" );
    assert_msg( rule2.getHead() != NULL, "Null head2" );
    const vector< XAtom >& head1Atoms = rule1.getHead()->getAtoms();
    const vector< XAtom >& head2Atoms = rule2.getHead()->getAtoms();
    if( !rule1.hasExistentialVariables() && !rule2.hasExistentialVariables() )
    {
        return isEquivalentTo(homomorphism,head1Atoms,head2Atoms);
    }

    XMapping tetaDatabase;
    unsigned currConst = 0;
    vector< XAtom > extendedHeadAtoms1;
    for( unsigned i=0; i<head1Atoms.size(); i++ )
    {
        vector< XTerm > extendedHeadAtomsTerms1;
        for( unsigned j=0; j<head1Atoms[i].getTerms().size(); j++ )
        {
            XMapping::iterator it = tetaDatabase.find(head1Atoms[i].getTerms().at(j));
            if( it == tetaDatabase.end() )
            {
                XTerm* dbTerm;

                if( head1Atoms[i].getTerms().at(j).isConst() )
                    dbTerm = program.createIntegerConstant(currConst++);
                else if( head1Atoms[i].getTerms().at(j).isStandardVar() )
                {
                    // If it is an existential variable it has not to be mapped.
                    if( rule1.isExistential(head1Atoms[i].getTerms().at(j)) )
                        dbTerm = program.createStandardVariable(head1Atoms[i].getTerms().at(j).getText());
                    else
                        dbTerm = program.createStringConstant(boost::to_lower_copy(head1Atoms[i].getTerms().at(j).getText()));
                }
                else
                    assert_msg( 0, "Nulls and unknown variables are not allowed here" );

                tetaDatabase.insert(pair< const XTerm&, const XTerm& >(head1Atoms[i].getTerms().at(j),*dbTerm));
                extendedHeadAtomsTerms1.push_back(*dbTerm);
                delete dbTerm;
            }
            else
                extendedHeadAtomsTerms1.push_back(it->second);
        }
        XAtom* dbAtom = program.createAtom(head1Atoms[i].getPredIndex(),extendedHeadAtomsTerms1);
        extendedHeadAtoms1.push_back(*dbAtom);
        delete dbAtom;
    }

    vector< XAtom > extendedHeadAtoms2;
    for( unsigned i=0; i<head2Atoms.size(); i++ )
    {
        vector< XTerm > extendedHeadAtomsTerms2;
        for( unsigned j=0; j<head2Atoms[i].getTerms().size(); j++ )
        {
            XMapping::const_iterator itHomomorphism = homomorphism.find(head2Atoms[i].getTerms().at(j));
            if( itHomomorphism != homomorphism.end() )
            {
                XMapping::const_iterator itTetaDatabase = tetaDatabase.find(itHomomorphism->second);
                if( itTetaDatabase != tetaDatabase.end() )
                {
                    extendedHeadAtomsTerms2.push_back(itTetaDatabase->second);
                }
                else
                {
                    // If the current term has been already mapped by homomorphism,
                    // but its image doesn't have a matching in tetaDatabase, it means
                    // that homomorphism is not extensible to the head because
                    // otherwise there would be a term which would map two different terms.
                    return false;
                }
            }
            else
            {
                if( head2Atoms[i].getTerms().at(j).isConst() )
                {
                    XMapping::const_iterator itTetaDatabase = tetaDatabase.find(head2Atoms[i].getTerms().at(j));
                    if( itTetaDatabase != tetaDatabase.end() )
                    {
                        extendedHeadAtomsTerms2.push_back(itTetaDatabase->second);
                    }
                    else
                    {
                        // There is a constants which doesn't appear in the other rule's head.
                        return false;
                    }
                }
                else
                {
                    // If it's a variable, it is an existential variable.
                    assert_msg( rule2.isExistential(head2Atoms[i].getTerms().at(j)), "Something went wrong" );
                    extendedHeadAtomsTerms2.push_back(head2Atoms[i].getTerms().at(j));
                }
            }
        }
        XAtom* dbAtom = program.createAtom(head2Atoms[i].getPredIndex(),extendedHeadAtomsTerms2);
        extendedHeadAtoms2.push_back(*dbAtom);
        delete dbAtom;
    }

    // Now we are interested in all possible homomorphisms.
    bool onlyFirst = false;
    vector< XMapping* > headHomomorphisms = computeHomomorphisms(extendedHeadAtoms1,extendedHeadAtoms2,onlyFirst);
    if( headHomomorphisms.size() == 0 )
        return false;

    // If at least an homomorphism h_i exists and can be inverted in a way such that
    // h_i^-1(extendedHeadAtoms2) = extendedHeadAtoms1 then extendedHeadAtoms2 and
    // extendedHeadAtoms1 are isomorphic.
    int indexValidIsomorphism = -1;
    for( unsigned i=0; i<headHomomorphisms.size(); i++ )
    {
        assert_msg( headHomomorphisms[i] != NULL, "Null homomorphism" );

        if( indexValidIsomorphism == -1
                && isInvertible(*headHomomorphisms[i],extendedHeadAtoms1,extendedHeadAtoms2) )
        {
                indexValidIsomorphism = i;
        }
        // REMIND to delete every i^th bodyHomomorphisms which you don't return.
        int iInt = i;
        if( indexValidIsomorphism != iInt )
            delete headHomomorphisms[i];
    }
    // If a valid isomorphism has been found, extend the isomorphism between the
    // rules' bodies in order to return a complete isomorphism for the pair of rules.
    if( indexValidIsomorphism != -1 )
    {
        for( unsigned i=0; i<headHomomorphisms[indexValidIsomorphism]->size(); i++ )
        {
            if( headHomomorphisms[indexValidIsomorphism]->at(i)->first.isStandardVar() )
            {
                assert_msg( homomorphism.find(headHomomorphisms[indexValidIsomorphism]->at(i)->first) == homomorphism.end(),
                        "This variable should have been avoided" );
                homomorphism.insert(
                        pair< const XTerm&, const XTerm& >(
                                headHomomorphisms[indexValidIsomorphism]->at(i)->first,
                                headHomomorphisms[indexValidIsomorphism]->at(i)->second));
            }
        }
        return true;
    }
    else
        return false;
}

bool
IsomorphismCheckByWasp::isEquivalentTo(
    const XMapping& homomorphism,
    const vector< XAtom >& atoms1,
    const vector< XAtom >& atoms2 ) const
{
    if( atoms1.size() != atoms2.size() )
        return false;

    vector< XAtom > imageAtoms;
    for( unsigned i=0; i<atoms2.size(); i++ )
    {
        vector< XTerm > invertedTerms;
        for( unsigned j=0; j<atoms2[i].getTerms().size(); j++ )
        {
            XMapping::const_iterator it = homomorphism.find(atoms2[i].getTerms().at(j));
            if( it != homomorphism.end() )
                invertedTerms.push_back(it->second);
            else
                invertedTerms.push_back(atoms2[i].getTerms().at(j));
        }
        XAtom* mappedAtom = program.createAtom(atoms2[i].getPredIndex(),invertedTerms);
        assert_msg( mappedAtom != NULL, "Null atom" );
        imageAtoms.push_back(*mappedAtom);
        delete mappedAtom;
    }

    // Compare 'atoms1' with 'imageAtoms', if they contain the same atoms they are equivalent
    vector< unsigned > uncheckedPositions;
    for( unsigned i=0; i<atoms1.size(); i++ )
            uncheckedPositions.push_back(i);
    bool ok = true;
    for( unsigned i=0; i<imageAtoms.size() && ok; i++ )
    {
        ok = false;
        for( unsigned j=0; j<uncheckedPositions.size() && !ok; j++ )
        {
            if( imageAtoms[i] == atoms1[uncheckedPositions[j]] )
            {
                ok = true;
                uncheckedPositions.erase(uncheckedPositions.begin()+j);
            }
        }
    }
    return (ok && uncheckedPositions.size() == 0);
}

pair< const XMapping&, const XRule& >
IsomorphismCheckByWasp::renameInput(
    const XRule& rule )
{
    XRenamingCache::const_iterator cache = renamingCache.find(rule);
    if( cache == renamingCache.end() )
    {
        unsigned varCounter = 1;
        XMapping renaming;
//        XMapping* inverseRenaming = new XMapping();
        const XHead* head = rule.getHead();
        const XBody* body = rule.getBody();
        assert_msg( head != NULL, "Null head or body" );
        const vector< XAtom >& headAtoms = head->getAtoms();
        vector< XAtom > renamedHeadAtoms;
        for( unsigned i=0; i<headAtoms.size(); i++ )
        {
            vector< XTerm > renamedTerms;
            for( unsigned j=0; j<headAtoms[i].getTerms().size(); j++ )
            {
                if( headAtoms[i].getTerms().at(j).isStandardVar() )
                {
                    XMapping::const_iterator it = renaming.find(headAtoms[i].getTerms().at(j));
                    if( it == renaming.end() )
                    {
                        stringstream ss;
                        ss << "V" << varCounter++;
                        XTerm* renamedTerm = program.createStandardVariable(ss.str());
                        renamedTerms.push_back(*renamedTerm);
                        renaming.insert(pair< const XTerm&, const XTerm& >(headAtoms[i].getTerms().at(j),*renamedTerm));
//                        inverseRenaming->insert(pair< XTerm, XTerm >(*renamedTerm,headAtoms[i].getTerms().at(j)));
                        delete renamedTerm;
                    }
                    else
                    {
                        renamedTerms.push_back(it->second);
                    }
                }
                else if( headAtoms[i].getTerms().at(j).isConst() )
                    renamedTerms.push_back(headAtoms[i].getTerms().at(j));
                else
                    assert_msg( 0, "Null terms and unknown variables are not allowed here" );
            }
            XAtom* renamedAtom = program.createAtom(headAtoms[i].getPredIndex(),renamedTerms);
            renamedHeadAtoms.push_back(*renamedAtom);
            delete renamedAtom;
        }
        XHead* renamedHead = NULL;
        if( rule.hasAtomicHead() )
        {
            assert_msg( renamedHeadAtoms.size() == 1,"Not valid atomic head" );
            renamedHead = program.createAtomicHead(renamedHeadAtoms[0]);
        }
        else if( rule.hasConjunctiveHead() )
            renamedHead = program.createConjunctiveHead(renamedHeadAtoms);
        else
            renamedHead = program.createDisjunctiveHead(renamedHeadAtoms);

        XBody* renamedBody = NULL;
        if( body != NULL )
        {
            vector< XLiteral > renamedBodyLiterals;
            for( unsigned i=0; i<body->size(); i++ )
            {
                vector< XTerm > renamedTerms;
                for( unsigned j=0; j<body->at(i).getAtom().getTerms().size(); j++ )
                {
                    if( body->at(i).getAtom().getTerms().at(j).isStandardVar() )
                    {
                        XMapping::const_iterator it = renaming.find(body->at(i).getAtom().getTerms().at(j));
                        if( it == renaming.end() )
                        {
                            stringstream ss;
                            ss << "V" << varCounter++;
                            XTerm* renamedTerm = program.createStandardVariable(ss.str());
                            renamedTerms.push_back(*renamedTerm);
                            renaming.insert(pair< const XTerm&, const XTerm& >(body->at(i).getAtom().getTerms().at(j),*renamedTerm));
//                            inverseRenaming->insert(pair< XTerm, XTerm >(*renamedTerm,body->at(i).getAtom().getTerms().at(j)));
                            delete renamedTerm;
                        }
                        else
                        {
                            renamedTerms.push_back(it->second);
                        }
                    }
                    else if( body->at(i).getAtom().getTerms().at(j).isConst() )
                        renamedTerms.push_back(body->at(i).getAtom().getTerms().at(j));
                    else
                        assert_msg( 0, "Null terms and unknown variables are not allowed here" );
                }
                XAtom* renamedAtom = program.createAtom(body->at(i).getAtom().getPredIndex(),renamedTerms);
                XLiteral* renamedLiteral = program.createLiteral(*renamedAtom);
                renamedBodyLiterals.push_back(*renamedLiteral);
                delete renamedLiteral;
                delete renamedAtom;
            }
            renamedBody = program.createBody(renamedBodyLiterals);
        }
        // This is the output rule, it mustn't be deleted.
        // The body and the head of the rule mustn't be deleted,
        // because the rule itself will do that.
        XRule* renamedRule = program.createRule(renamedHead,renamedBody);
        pair< XRenamingCache::iterator, bool > res = renamingCache.insert(rule,renaming,*renamedRule);
        delete renamedRule;
        return pair< const XMapping&, const XRule& >(res.first->second.getRenaming(),res.first->second.getRenamedRule());
    }
    else
    {
        return pair< const XMapping&, const XRule& >(cache->second.getRenaming(),cache->second.getRenamedRule());
    }
}


pair< const XMapping&, vector< XAtom >* >
IsomorphismCheckByWasp::renameInput(
    const XRule& rule,
    const vector< XAtom >& atoms )
{
    // First of all, retrieve the renaming for the current rule.
    // If such a renaming has not been cached yet, create and store it in 'renamingCache'.
    const XMapping* cachedRenaming = NULL;
    XRenamingCache::const_iterator cache = renamingCache.find(rule);
    if( cache == renamingCache.end() )
    {
        pair< const XMapping&, const XRule& > result = renameInput(rule);
        cachedRenaming = &result.first;
    }
    else
    {
        cachedRenaming = &cache->second.getRenaming();
    }
    assert_msg( cachedRenaming != NULL, "An error has occurred" );
    // Rename the input atom set by means of 'cachedRenaming'.
    // Notice that, the atom set is not cached because, for each
    // renaming of the same rule, the atom set to be renamed may vary.
    vector< XAtom >* renamedAtoms = new vector< XAtom >();
    for( unsigned i=0; i<atoms.size(); i++ )
    {
        vector< XTerm > renamedTerms;
        for ( unsigned j=0; j<atoms[i].getTerms().size(); j++ )
        {
            if( atoms[i].getTerms().at(j).isStandardVar() )
            {
                XMapping::const_iterator it = cachedRenaming->find(atoms[i].getTerms().at(j));
                assert_msg( it != cachedRenaming->end(), "These atoms should belong to the input rule" );
                renamedTerms.push_back(it->second);
            }
            else if( atoms[i].getTerms().at(j).isConst() )
                renamedTerms.push_back(atoms[i].getTerms().at(j));
        }
        XAtom* renamedAtom = program.createAtom(atoms[i].getPredIndex(),renamedTerms);
        renamedAtoms->push_back(*renamedAtom);
        delete renamedAtom;
    }
    return pair< const XMapping&, vector< XAtom >* >(*cachedRenaming,renamedAtoms);
}

XMapping*
IsomorphismCheckByWasp::unrenameOutput(
    const XMapping* output,
    const XMapping* inverseRenaming ) const
{
    assert_msg( output != NULL, "Null homomorphism in output" );
    assert_msg( inverseRenaming != NULL, "Null renaming" );

    XMapping* unrenamedOutput = new XMapping();
    for( unsigned i=0; i<output->size(); i++ )
    {
        XMapping::const_iterator itOutput = output->at(i);
        if( itOutput->first.isConst() )
        {
            assert_msg( itOutput->first == itOutput->second, "Not valid homomorphism" );
            unrenamedOutput->insert(pair< const XTerm&, const XTerm& >(itOutput->first,itOutput->second));
        }
        else if( itOutput->second.isConst() )
        {
            XMapping::const_iterator itRenamingFirst = inverseRenaming->find(itOutput->first);
            assert_msg( itRenamingFirst != inverseRenaming->end(), "Variable renaming not found!" );
            unrenamedOutput->insert(pair< const XTerm&, const XTerm& >(itRenamingFirst->second,itOutput->second));
        }
        else
        {
            XMapping::const_iterator itRenamingFirst = inverseRenaming->find(itOutput->first);
            XMapping::const_iterator itRenamingSecond = inverseRenaming->find(itOutput->second);
            assert_msg( ( itRenamingFirst != inverseRenaming->end() && itRenamingSecond != inverseRenaming->end() ),
                    "Variable renaming not found!" );
            unrenamedOutput->insert(pair< const XTerm&, const XTerm& >(itRenamingFirst->second,itRenamingSecond->second));
        }
    }
    return unrenamedOutput;
}
