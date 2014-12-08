/* 
 * File:   XMGUCache.cpp
 * Author: pierfrancesco
 *
 * Created on 07 dicembre 2014, 16.20
 */

#include "XMGUCache.h"
#include "../../util/Assert.h"
#include <sstream>

using namespace DLV2::REWRITERS;
using namespace std;

XMGUCache::const_iterator
XMGUCache::find(
    const vector< XAtom >& keySet1,
    const std::vector< XAtom >& keySet2 ) const
{
    size_t key = getHashCode(keySet1,keySet2);
    return mguMap.find(key);
}

XMGUCache::iterator
XMGUCache::insert(
    const vector< XAtom >& keySet1,
    const vector< XAtom >& keySet2,
    const XMapping& mgu )
{
    size_t key = getHashCode(keySet1,keySet2);
    assert_msg( mguMap.find(key) == mguMap.end(), "Not valid entry, this mgu has already been cached" );
    pair< iterator, bool > res = mguMap.insert(pair< size_t, XMGUCacheElement >(key,XMGUCacheElement(mgu)));
    return res.first;
}

XMGUCache::iterator
XMGUCache::insert(
    const vector< XAtom >& keySet1,
    const vector< XAtom >& keySet2 )
{
    size_t key = getHashCode(keySet1,keySet2);
    assert_msg( mguMap.find(key) == mguMap.end(), "Not valid entry, this mgu has already been cached" );
    pair< iterator, bool > res = mguMap.insert(pair< size_t, XMGUCacheElement >(key,XMGUCacheElement()));
    return res.first;
}

size_t
XMGUCache::getHashCode(
    const vector< XAtom >& keySet1,
    const std::vector< XAtom >& keySet2 ) const
{
    stringstream ss;
    for( unsigned i=0; i<keySet1.size(); i++ )
        ss << keySet1[i] << ",";
    for( unsigned i=0; i<keySet2.size(); i++ )
    {
        ss << keySet2[i];
        if( i < keySet2.size()-1 )
            ss << ",";
    }
    hash< string > stringHasher;
    return stringHasher(ss.str());
}
