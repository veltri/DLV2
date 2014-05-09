/* 
 * File:   DepGraphOnlyPositiveEdgesStrategy.h
 * Author: cesco
 *
 * Created on 8 maggio 2014, 18.01
 */

#ifndef DEPGRAPHONLYPOSITIVEEDGESSTRATEGY_H
#define	DEPGRAPHONLYPOSITIVEEDGESSTRATEGY_H

#include "DepGraphNoStrategy.h"
#include "../util/Assert.h"
#include "../util/Constants.h"

namespace DLV2
{

    // Strategy for positive dependency graphs.
    
    class DepGraphOnlyPositiveEdgesStrategy: public DepGraphNoStrategy {
    public:
        DepGraphOnlyPositiveEdgesStrategy() {}
        virtual ~DepGraphOnlyPositiveEdgesStrategy() {}
        
        virtual void edge( unsigned label ) const { assert( label == POSITIVE_EDGE ); }
        virtual bool isPositive() const { return true; }
    };
    
};

#endif	/* DEPGRAPHONLYPOSITIVEEDGESSTRATEGY_H */

