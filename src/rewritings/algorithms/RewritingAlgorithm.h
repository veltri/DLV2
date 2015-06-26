/* 
 * File:   RewritingAlgorithm.h
 * Author: pierfrancesco
 *
 * Created on 03 dicembre 2014, 13.14
 */

#ifndef REWRITINGALGORITHM_H
#define REWRITINGALGORITHM_H

#include "../data/XProgram.h"
#include <vector>

namespace DLV2{ namespace REWRITERS{

    class RewritingAlgorithm {
    public:
        RewritingAlgorithm( XProgram& input ): inputProgram(input) { }
        virtual ~RewritingAlgorithm() { }

        virtual std::vector< XRule* > rewrite() = 0;
        virtual void printStatistics() const = 0;

    protected:
        XProgram& inputProgram;
    };

};};

#endif /* REWRITINGALGORITHM_H */
