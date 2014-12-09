/* 
 * File:   XMGUCacheElement.h
 * Author: pierfrancesco
 *
 * Created on 08/dic/2014, 02:45:41
 */

#ifndef XMGUCACHEELEMENT_H
#define XMGUCACHEELEMENT_H

#include "XIterableMap.h"
#include "../../util/Assert.h"

namespace DLV2{ namespace REWRITERS{

    class XMGUCacheElement {
    public:
        XMGUCacheElement( const XMapping& unifier );
        XMGUCacheElement(): mayExist(false), mgu(NULL) { }
        XMGUCacheElement( const XMGUCacheElement& elem );
        ~XMGUCacheElement();

        bool exists() const { return mayExist; }
        const XMapping* getMgu() const { return mgu; }

    private:
        bool mayExist;
        XMapping* mgu;

    };

};};

#endif /* XMGUCACHEELEMENT_H */
