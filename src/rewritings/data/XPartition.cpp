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
 * File:   XPartition.cpp
 * Author: pierfrancesco
 *
 * Created on 09 gennaio 2015, 18.23
 */

#include "XPartition.h"

#include "../../util/Assert.h"
#include "../../util/Trace.h"
#include "../../util/Options.h"

using namespace std;
using namespace DLV2::REWRITERS;


XPartition::XPartition(
    XProgram& p ):
        program(p),
        classes(),
        substitution()
{
}

XPartition::XPartition(
    const XPartition& partition ):
        program(partition.program),
        classes(),
        substitution()
{
    for( list< XEquivalenceClass >::const_iterator itEqClass = partition.classes.begin();
            itEqClass != partition.classes.end();
            itEqClass++ )
    {
        assert_msg( itEqClass->size() > 0, "Invalid equivalence class" );
        // Pick up an element from the current class and add an equivalence
        // between it and all the rest of the class.
        const XTerm& firstTerm = itEqClass->at(0)->first;
        const XTermType& firstTermType = itEqClass->typeOfElementAt(0);
        for( unsigned i=1; i<itEqClass->size(); i++ )
            this->addEquivalence(firstTerm,firstTermType,itEqClass->at(i)->first,itEqClass->typeOfElementAt(i));
//        for( unsigned i=0; i<itEqClass->getStandardVars().size(); i++ )
//            this->addEquivalence(firstTerm,firstTermType,itEqClass->getStandardVars().at(i)->first,Variable);
//        for( unsigned i=0; i<itEqClass->getFrontierVars().size(); i++ )
//            this->addEquivalence(firstTerm,firstTermType,itEqClass->getFrontierVars().at(i)->first,FrontierVariable);
//        for( unsigned i=0; i<itEqClass->getExistentialVars().size(); i++ )
//            this->addEquivalence(firstTerm,firstTermType,itEqClass->getExistentialVars().at(i)->first,ExistentialVariable);
//        for( unsigned i=0; i<itEqClass->getConstants().size(); i++ )
//            this->addEquivalence(firstTerm,firstTermType,itEqClass->getConstants().at(i)->first,Constant);
    }
}

bool
XPartition::isValid() const
{
    for( typename list< XEquivalenceClass >::const_iterator it = classes.begin();
            it != classes.end();
            it++ )
        if( !it->isValid() )
            return false;
    return true;
}

void
XPartition::addEquivalence(
    const XTerm& term1,
    const XTermType& typeTerm1,
    const XTerm& term2,
    const XTermType& typeTerm2 )
{
    trace_msg( rewriting, 4, "Add equivalence between: " << term1 << " and " << term2 );
    XPartitionMap::iterator it1 = substitution.find(term1);
    XPartitionMap::iterator it2 = substitution.find(term2);
    if( it1 != substitution.end() && it2 != substitution.end() )
    {
        // Merge their equivalence classes, if they are different.
        if( it1->second != it2->second )
        {
            trace_msg( rewriting, 4, "They already belong to the partition, but their classes were different, merge them." );
            it1->second->merge(*it2->second);
            list< XEquivalenceClass >::iterator equivalenceClassToCancel = it2->second;
            // Update the iterator to the equivalence class for all of its elements (constants, existential variables, etc).
            // Remind: an equivalence class is designed to store just iterators to elements from map XPartitionMap.
            for( unsigned i=0; i<it2->second->getStandardVars().size(); i++ )
                substitution[it2->second->getStandardVars().at(i)->first] = it1->second;
            for( unsigned i=0; i<it2->second->getFrontierVars().size(); i++ )
                substitution[it2->second->getFrontierVars().at(i)->first] = it1->second;
            for( unsigned i=0; i<it2->second->getExistentialVars().size(); i++ )
                substitution[it2->second->getExistentialVars().at(i)->first] = it1->second;
            for( unsigned i=0; i<it2->second->getConstants().size(); i++ )
                substitution[it2->second->getConstants().at(i)->first] = it1->second;
            classes.erase(equivalenceClassToCancel);
        }
        // Don't do anything, otherwise.
    }
    else if( it1 != substitution.end() )
    {
        // First of all, insert the unknown term into the map.
        pair< XPartitionMap::iterator, bool > res = substitution.insert(
                pair< const XTerm&, typename std::list< XEquivalenceClass >::iterator >(term2,it1->second));
        assert_msg( res.second, "The second term was already in the map" );
        it1->second->pushTerm(res.first,typeTerm2);
    }
    else if( it2 != substitution.end() )
    {
        // First of all, insert the unknown term into the map.
        pair< XPartitionMap::iterator, bool > res = substitution.insert(
                pair< const XTerm&, typename std::list< XEquivalenceClass >::iterator >(term1,it2->second));
        assert_msg( res.second, "The first term was already in the map" );
        it2->second->pushTerm(res.first,typeTerm1);
    }
    else
    {
        // First of all, create a new equivalence class.
        XEquivalenceClass* eqClass = program.createEquivalenceClass();
        std::list< XEquivalenceClass >::iterator itNewClass = classes.insert(classes.end(),*eqClass);
        // Now, insert the two terms into the map.
        pair< XPartitionMap::iterator, bool > res1 =
                substitution.insert(pair< const XTerm&, typename std::list< XEquivalenceClass >::iterator >(term1,itNewClass));
        assert_msg( res1.second, "The first term was already in the map" );
        pair< XPartitionMap::iterator, bool > res2 =
                substitution.insert(pair< const XTerm&, typename std::list< XEquivalenceClass >::iterator >(term2,itNewClass));
        assert_msg( res2.second, "The second term was already in the map" );
        // Finally, add the terms to the new equivalence class.
        itNewClass->pushTerm(res1.first,typeTerm1);
        itNewClass->pushTerm(res2.first,typeTerm2);
        delete eqClass;
    }
}

void
XPartition::merge(
    const XPartition& partition )
{
    for( list< XEquivalenceClass >::const_iterator itEqClass = partition.classes.begin();
            itEqClass != partition.classes.end();
            itEqClass++ )
    {
        assert_msg( itEqClass->size() > 0, "Invalid equivalence class" );
        // Pick up an element from the current class and add an equivalence
        // between it and all the rest of the class.
        const XTerm& firstTerm = itEqClass->at(0)->first;
        const XTermType& firstTermType = itEqClass->typeOfElementAt(0);
        for( unsigned i=1; i<itEqClass->size(); i++ )
            this->addEquivalence(firstTerm,firstTermType,itEqClass->at(i)->first,itEqClass->typeOfElementAt(i));
//        for( unsigned i=0; i<itEqClass->getStandardVars().size(); i++ )
//            this->addEquivalence(firstTerm,firstTermType,itEqClass->getStandardVars().at(i)->first,Variable);
//        for( unsigned i=0; i<itEqClass->getFrontierVars().size(); i++ )
//            this->addEquivalence(firstTerm,firstTermType,itEqClass->getFrontierVars().at(i)->first,FrontierVariable);
//        for( unsigned i=0; i<itEqClass->getExistentialVars().size(); i++ )
//            this->addEquivalence(firstTerm,firstTermType,itEqClass->getExistentialVars().at(i)->first,ExistentialVariable);
//        for( unsigned i=0; i<itEqClass->getConstants().size(); i++ )
//            this->addEquivalence(firstTerm,firstTermType,itEqClass->getConstants().at(i)->first,Constant);
    }
}

void
XPartition::mergePartitionToBeRenamed(
    const XPartition& partitionToBeRenamed,
    const XMapping& renaming )
{
    for( list< XEquivalenceClass >::const_iterator itEqClass = partitionToBeRenamed.classes.begin();
            itEqClass != partitionToBeRenamed.classes.end();
            itEqClass++ )
    {
        assert_msg( itEqClass->size() > 0, "Invalid equivalence class" );
        // Pick up an element from the current class and add an equivalence
        // between it and all the rest of the class. Before doing that, check
        // whether the term needs to be renamed.
        const XTerm* ptrFirstTerm;
        XMapping::const_iterator itFirstTerm = renaming.find(itEqClass->at(0)->first);
        if( itFirstTerm == renaming.end() )
            ptrFirstTerm = &(itEqClass->at(0)->first);
        else
            ptrFirstTerm = &(itFirstTerm->second);
        const XTermType& firstTermType = itEqClass->typeOfElementAt(0);
        for( unsigned i=1; i<itEqClass->size(); i++ )
        {
            XMapping::const_iterator itSecondTerm = renaming.find(itEqClass->at(i)->first);
            if( itSecondTerm == renaming.end() )
                this->addEquivalence(*ptrFirstTerm,firstTermType,itEqClass->at(i)->first,itEqClass->typeOfElementAt(i));
            else
                this->addEquivalence(*ptrFirstTerm,firstTermType,itSecondTerm->second,itEqClass->typeOfElementAt(i));
        }
//        for( unsigned i=0; i<itEqClass->getStandardVars().size(); i++ )
//        {
//            XMapping::const_iterator itSecondTerm = renaming.find(itEqClass->getStandardVars().at(i)->first);
//            if( itSecondTerm == renaming.end() )
//                this->addEquivalence(*ptrFirstTerm,firstTermType,itEqClass->getStandardVars().at(i)->first,Variable);
//            else
//                this->addEquivalence(*ptrFirstTerm,firstTermType,itSecondTerm->second,Variable);
//        }
//        for( unsigned i=0; i<itEqClass->getFrontierVars().size(); i++ )
//        {
//            XMapping::const_iterator itSecondTerm = renaming.find(itEqClass->getFrontierVars().at(i)->first);
//            if( itSecondTerm == renaming.end() )
//                this->addEquivalence(*ptrFirstTerm,firstTermType,itEqClass->getFrontierVars().at(i)->first,FrontierVariable);
//            else
//                this->addEquivalence(*ptrFirstTerm,firstTermType,itSecondTerm->second,FrontierVariable);
//        }
//        for( unsigned i=0; i<itEqClass->getExistentialVars().size(); i++ )
//        {
//            XMapping::const_iterator itSecondTerm = renaming.find(itEqClass->getExistentialVars().at(i)->first);
//            if( itSecondTerm == renaming.end() )
//                this->addEquivalence(*ptrFirstTerm,firstTermType,itEqClass->getExistentialVars().at(i)->first,ExistentialVariable);
//            else
//                this->addEquivalence(*ptrFirstTerm,firstTermType,itSecondTerm->second,ExistentialVariable);
//        }
//        for( unsigned i=0; i<itEqClass->getConstants().size(); i++ )
//        {
//            // Constants are never renamed.
//            this->addEquivalence(*ptrFirstTerm,firstTermType,itEqClass->getConstants().at(i)->first,Constant);
//        }
    }
}

const XTerm&
XPartition::getMapping(
    const XTerm& termToBeMapped )
{
    XPartitionMap::iterator it = substitution.find(termToBeMapped);
    // If a term has not been mapped yet, it was not involved in
    // the unification process; anyway, it has to be mapped to a new
    // term name in order to avoid clutters between variable names
    // of the rewriting rule under construction and the ones from
    // the existent rules.
    if( it == substitution.end() )
    {
        // Create a new equivalence class for this term.
        XEquivalenceClass* eqClass = program.createEquivalenceClass();
        std::list< XEquivalenceClass >::iterator itNewClass = classes.insert(classes.end(),*eqClass);
        // Now, insert the term into the map.
        pair< XPartitionMap::iterator, bool > res =
                substitution.insert(pair< const XTerm&, typename std::list< XEquivalenceClass >::iterator >(termToBeMapped,itNewClass));
        assert_msg( res.second, "The term was already in the map" );
        // Finally, add the term to the new equivalence class.
        if( termToBeMapped.isStandardVar() )
            itNewClass->pushTerm(res.first,Variable);
        else if( termToBeMapped.isConst() )
            itNewClass->pushTerm(res.first,Constant);
        else
            assert_msg( 0, "Term type not valid" );
        delete eqClass;

        return itNewClass->getRepresentativeTerm();
    }
    else
        return it->second->getRepresentativeTerm();
}

bool
XPartition::isPartitionedWithAnExistentialVariable(
    const XTerm& term ) const
{
    XPartitionMap::const_iterator it = substitution.find(term);
    assert_msg( it != substitution.end(), "Not a valid term" );
    return it->second->getExistentialVars().size() > 0;
}
