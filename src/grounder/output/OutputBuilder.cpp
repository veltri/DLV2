/*
 * OutputBuilder.cpp
 *
 *  Created on: Jul 7, 2015
 *      Author: davide
 */

#include "NumericOutputBuilder.h"

namespace DLV2 {
namespace grounder {

OutputBuilder* OutputBuilder::outputBuilder=nullptr;


OutputBuilder* OutputBuilder::getInstance() {
	if(outputBuilder==nullptr)
		switch(Options::globalOptions()->getOutputFormat()){
//			case OUTPUT_TEXTUAL:
//				break;
			default:
				outputBuilder=new NumericOutputBuilder;
				break;
		}

	return outputBuilder;
}

} /* namespace grounder */
} /* namespace DLV2 */
