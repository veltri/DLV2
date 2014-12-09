/* 
 * File:   XMGUCacheElement.cpp
 * Author: pierfrancesco
 *
 * Created on 09 dicembre 2014, 20.22
 */

#include "XMGUCacheElement.h"

using namespace DLV2::REWRITERS;
using namespace std;

XMGUCacheElement::XMGUCacheElement(
    const XMapping& unifier ):
        mayExist(true)
{
    mgu = new XMapping(unifier);
}

XMGUCacheElement::XMGUCacheElement(
    const XMGUCacheElement& elem ):
        mayExist(elem.mayExist)
{
    if( elem.mgu != NULL )
        mgu = new XMapping(*elem.mgu);
}

XMGUCacheElement::~XMGUCacheElement()
{
    if( mgu != NULL )
        delete mgu;
}
