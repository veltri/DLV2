/* 
 * File:   XRenamingCache.cpp
 * Author: pierfrancesco
 *
 * Created on 05 dicembre 2014, 20.59
 */

#include "XRenamingCache.h"
#include "../../util/Assert.h"

using namespace DLV2::REWRITERS;
using namespace std;

XRenamingCache::const_iterator
XRenamingCache::find(
    const XRule& key ) const
{
    hash< XRule > ruleHasher;
    size_t ruleHash = ruleHasher(key);
    return renamingsMap.find(ruleHash);
}

pair< XRenamingCache::iterator, bool >
XRenamingCache::insert(
    const XRule& key,
    const XMapping& renaming,
    const XRule& renamedRule )
{
    hash< XRule > ruleHasher;
    size_t ruleHash = ruleHasher(key);
    assert_msg( renamingsMap.find(ruleHash) == renamingsMap.end(), "Renaming already cached" );
    return renamingsMap.insert(pair< size_t, const XRenaming& >(ruleHash,XRenaming(renaming,renamedRule)));
}

//pair< const XMapping*, const XRule* >
//XRenamingCache::insertRenaming(
//    const XRule& key,
//    const XMapping& renaming )
//{
//    hash< XRule > ruleHasher;
//    RenamingMapKey ruleHash = ruleHasher(key);
//    assert_msg( renamingsMap.find(ruleHash) == renamingsMap.end(), "Not valid entry, this renaming has already been cached" );
//    renamings.push_back(renaming);
//    RenamingIndex idx = renamings.size()-1;
//    pair< RenamingIndex, RuleIndex > element(idx,-1);
//    renamingsMap.insert(pair< RenamingMapKey, RenamingMapValue >(ruleHash,element));
//    const XMapping* ptrRenaming = &(renamings[idx]);
//    return pair< const XMapping*, const XRule* >(ptrRenaming,NULL);
//}
//
//pair< const XMapping*, const XRule* >
//XRenamingCache::insertRenamedRule(
//    const XRule& key,
//    const XRule& renamedRule )
//{
//    hash< XRule > ruleHasher;
//    RenamingMapKey ruleHash = ruleHasher(key);
//    unordered_map< RenamingMapKey, RenamingMapValue >::iterator resultRenaming = renamingsMap.find(ruleHash);
//    assert_msg( resultRenaming != renamingsMap.end(), "Not valid entry, not recognized" );
//    assert_msg( resultRenaming->second.second == -1, "Double insertion" );
//    renamedRules.push_back(renamedRule);
//    RuleIndex ruleIdx = renamedRules.size()-1;
//    resultRenaming->second.second = ruleIdx;
//    assert_msg( ( 0 <= resultRenaming->second.first && resultRenaming->second.first < (int)renamings.size() ),
//                    "Index out of range" );
//    const XMapping* ptrRenaming = &(renamings[resultRenaming->second.first]);
//    const XRule* ptrRule = &(renamedRules[ruleIdx]);
//    return pair< const XMapping*, const XRule* >(ptrRenaming,ptrRule);
//}
//
//pair< const XMapping*, const XRule* >
//XRenamingCache::insertRenamingAndRenamedRule(
//    const XRule& key,
//    const XMapping& renaming,
//    const XRule& renamedRule )
//{
//    hash< XRule > ruleHasher;
//    RenamingMapKey ruleHash = ruleHasher(key);
//    assert_msg( renamingsMap.find(ruleHash) == renamingsMap.end(), "Not valid entry, this renaming has already been cached" );
//    renamings.push_back(renaming);
//    RenamingIndex renamingIdx = renamings.size()-1;
//    renamedRules.push_back(renamedRule);
//    RuleIndex ruleIdx = renamedRules.size()-1;
//    pair< RenamingIndex, RuleIndex > element(renamingIdx,ruleIdx);
//    renamingsMap.insert(pair< RenamingMapKey, const RenamingMapValue& >(ruleHash,element));
//    const XMapping* ptrRenaming = &(renamings[renamingIdx]);
//    const XRule* ptrRule = &(renamedRules[ruleIdx]);
//    return pair< const XMapping*, const XRule* >(ptrRenaming,ptrRule);
//}
//
//pair< const XMapping*, const XRule* >
//XRenamingCache::getRenaming(
//    const XRule& key ) const
//{
//    hash< XRule > ruleHasher;
//    RenamingMapKey ruleHash = ruleHasher(key);
//    unordered_map< RenamingMapKey, RenamingMapValue >::const_iterator resultRenaming = renamingsMap.find(ruleHash);
//    if( resultRenaming == renamingsMap.end() )
//        return pair< const XMapping*, const XRule* >(NULL,NULL);
//    const XMapping* ptrRenaming = NULL;
//    const XRule* ptrRule = NULL;
//    assert_msg( ( 0 <= resultRenaming->second.first && resultRenaming->second.first < (int)renamings.size() ),
//            "Index out of range" );
//    ptrRenaming = &(renamings[resultRenaming->second.first]);
//    if( resultRenaming->second.second != -1 )
//    {
//        assert_msg( ( 0 <= resultRenaming->second.second && resultRenaming->second.second < (int)renamedRules.size() ),
//                "Index out of range" );
//        ptrRule = &(renamedRules[resultRenaming->second.second]);
//    }
//    return pair< const XMapping*, const XRule* >(ptrRenaming,ptrRule);
//}
