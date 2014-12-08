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
        XMGUCacheElement( const XMapping& unifier ): mgu(new XMapping(unifier)), mayExist(true) { }
        XMGUCacheElement(): mgu(NULL), mayExist(false) { }
        ~XMGUCacheElement() { if( mgu != NULL ) delete mgu; }

        bool exists() const { return mayExist; }
        const XMapping* getMgu() const { return mgu; }

    private:
        XMapping* mgu;
        bool mayExist;
    };

};};

#endif /* XMGUCACHEELEMENT_H */
