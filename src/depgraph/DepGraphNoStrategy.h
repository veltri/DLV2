/* 
 * File:   DepGraphNoStrategy.h
 * Author: cesco
 *
 * Created on 8 maggio 2014, 18.00
 */

#ifndef DEPGRAPHNOSTRATEGY_H
#define	DEPGRAPHNOSTRATEGY_H

#include "../util/Assert.h"

namespace DLV2
{
    // (Default) strategy for dependency graphs with eventual negated edges.
    
    class DepGraphNoStrategy {
    public:
        DepGraphNoStrategy() {}
        virtual ~DepGraphNoStrategy() {}
        
        virtual void edge( unsigned ) const { }
        virtual bool isPositive() const { return false; }
    };
    
};

#endif	/* DEPGRAPHNOSTRATEGY_H */

