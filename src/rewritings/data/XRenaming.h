/* 
 * File:   XRenaming.h
 * Author: pierfrancesco
 *
 * Created on 08 dicembre 2014, 00.21
 */

#ifndef XRENAMING_H
#define XRENAMING_H

#include "XIterableMap.h"
#include "XRule.h"

namespace DLV2{ namespace REWRITERS{

    class XRenaming {
    public:
        XRenaming( const XMapping& ren, const XRule& rule ): renaming(ren), renamedRule(rule) { }
        ~XRenaming() { }

        const XMapping& getRenaming() const { return renaming; }
        const XRule& getRenamedRule() const { return renamedRule; }

    private:
        XMapping renaming;
        XRule renamedRule;
    };

};};

#endif /* XRENAMING_H */
