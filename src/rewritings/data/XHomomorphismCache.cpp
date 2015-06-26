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
 * File:   XHomomorphismCache.cpp
 * Author: cesco
 *
 * Created on 22 maggio 2015, 12.21
 */

#include "XHomomorphismCache.h"

#include "XProgram.h"
#include "XIterableMap.h"
#include <sstream>

using namespace DLV2::REWRITERS;
using namespace std;

pair< bool, const bool& >
XHomomorphismCache::inCache(
    const pair< const XAtom&, const XAtom& >& key ) const
{
    size_t hash1 = getCanonicalHash(key.first);
    unordered_map< size_t, unordered_map< size_t, bool > >::const_iterator itFirst = cacheMap.find(hash1);
    if( itFirst == cacheMap.end() )
        return pair< bool, const bool& >(false,false);
    // Else..
    hash< XAtom > atomHash2;
    size_t hash2 = atomHash2(key.second);
    unordered_map< size_t, bool >::const_iterator itSecond = itFirst->second.find(hash2);
    if( itSecond == itFirst->second.end() )
        return pair< bool, const bool& >(false,false);
    else
    {
        return pair< bool, const bool& >(true,itSecond->second);
    }
}

void
XHomomorphismCache::cache(
    const pair< const XAtom&, const XAtom& >& key,
    const bool& value )
{
    size_t hash1 = getCanonicalHash(key.first);
    hash< XAtom > atomHash2;
    size_t hash2 = atomHash2(key.second);
    unordered_map< size_t, unordered_map< size_t, bool > >::iterator itFirst = cacheMap.find(hash1);
    if( itFirst == cacheMap.end() )
    {
        unordered_map< size_t, bool > homomorphismsMap;
        homomorphismsMap.insert(pair< size_t, bool >(hash2,value));
        cacheMap.insert(pair< size_t, unordered_map< size_t, bool > >(hash1,homomorphismsMap));
    }
    else
    {
        itFirst->second.insert(pair< size_t, bool >(hash2,value));
    }
}

size_t
XHomomorphismCache::getCanonicalHash(
    const XAtom& atom ) const
{
    unsigned varCounter = 0;
    XMapping renaming;
    vector< XTerm > renamedTerms;
    for( unsigned i=0; i<atom.getTerms().size(); i++ )
    {
        const XTerm& term = atom.getTerms().at(i);
        if( term.isStandardVar() )
        {
            XMapping::const_iterator it = renaming.find(term);
            if( it == renaming.end() )
            {
                stringstream ss;
                // No clutters among variable names are thrown if variables like "K.." are used,
                // because the second atom (in the homomorphism check) has only variables whose names start with "X..".
                ss << "K" << varCounter++;
                XTerm* renamedTerm = program.createStandardVariable(ss.str());
                renaming.insert(pair< const XTerm&, const XTerm& >(term,*renamedTerm));
                renamedTerms.push_back(*renamedTerm);
                delete renamedTerm;
            }
            else
                renamedTerms.push_back(it->second);
        }
        else
            renamedTerms.push_back(term);
    }
    XAtom* renamedAtom = program.createAtom(atom.getPredIndex(),renamedTerms,atom.isTrueNegated());
    hash< XAtom > atomHash;
    size_t hash = atomHash(*renamedAtom);
    delete renamedAtom;
    return hash;
}
