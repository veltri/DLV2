/* 
 * File:   XRenamingCache.h
 * Author: pierfrancesco
 *
 * Created on 05 dicembre 2014, 20.10
 */

#ifndef XRENAMINGCACHE_H
#define XRENAMINGCACHE_H

#include <unordered_map>
#include <vector>
#include "XRule.h"
#include "XIterableMap.h"
#include "XRenaming.h"

namespace DLV2{ namespace REWRITERS{

    class XRenamingCache {
    public:
        typedef std::unordered_map< size_t, XRenaming >::const_iterator const_iterator;
        typedef std::unordered_map< size_t, XRenaming >::iterator iterator;

        XRenamingCache(): renamingsMap() { }
        ~XRenamingCache() { }

        const_iterator begin() const { return renamingsMap.begin(); }
        const_iterator end() const { return renamingsMap.end(); }
        const_iterator find( const XRule& key ) const;
        std::pair< iterator, bool > insert( const XRule& key, const XMapping& renaming, const XRule& renamedRule );

    private:
        std::unordered_map< size_t, XRenaming > renamingsMap;

    };

};};

#endif /* XRENAMINGCACHE_H */
