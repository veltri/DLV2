/* 
 * File:   XMGUCache.h
 * Author: pierfrancesco
 *
 * Created on 07 dicembre 2014, 16.09
 */

#ifndef XMGUCACHE_H
#define XMGUCACHE_H

#include <unordered_map>
#include <vector>
#include "XAtom.h"
#include "XIterableMap.h"
#include "XMGUCacheElement.h"

namespace DLV2{ namespace REWRITERS{

    class XMGUCache {
    public:
        typedef std::unordered_map< size_t, XMGUCacheElement>::const_iterator const_iterator;
        typedef std::unordered_map< size_t, XMGUCacheElement >::iterator iterator;

        XMGUCache(): mguMap() { }
        ~XMGUCache() { }

        const_iterator begin() const { return mguMap.begin(); }
        const_iterator end() const { return mguMap.end(); }
        const_iterator find( const std::vector< XAtom >& keySet1, const std::vector< XAtom >& keySet2 ) const;
        iterator insert( const std::vector< XAtom >& kSet1, const std::vector< XAtom >& kSet2, const XMapping& mgu );
        // When two atom sets are not unifiable, they are cached with a null MGU.
        iterator insert( const std::vector< XAtom >& kSet1, const std::vector< XAtom >& kSet2 );

    private:
        size_t getHashCode( const std::vector< XAtom >& keySet1, const std::vector< XAtom >& keySet2 ) const;

        std::unordered_map< size_t, XMGUCacheElement > mguMap;
    };

};};

#endif /* XMGUCACHE_H */
