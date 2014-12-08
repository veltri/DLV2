/* 
 * File:   RewritingAlgorithm.h
 * Author: pierfrancesco
 *
 * Created on 03 dicembre 2014, 13.14
 */

#ifndef REWRITINGALGORITHM_H
#define REWRITINGALGORITHM_H

#include "../data/XProgram.h"

using DLV2::REWRITERS::XProgram;

namespace DLV2{ namespace REWRITERS{

    class IsomorphismCheckStrategy;

    class RewritingAlgorithm {
    public:
        RewritingAlgorithm( IsomorphismCheckStrategy* isoCheck ): isomorphismCheckStrategy(isoCheck) { }
        virtual ~RewritingAlgorithm() { }

        XProgram* rewrite( const XProgram& input ) = 0;

    private:
        IsomorphismCheckStrategy* isomorphismCheckStrategy;

    };

};};

#endif /* REWRITINGALGORITHM_H */
