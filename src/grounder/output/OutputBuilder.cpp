/*
 * OutputBuilder.cpp
 *
 *  Created on: Jul 7, 2015
 *      Author: davide
 */

#include "NumericOutputBuilder.h"
#include "TextualOutputBuilder.h"

namespace DLV2 {
namespace grounder {

OutputBuilder* OutputBuilder::outputBuilder=nullptr;


OutputBuilder* OutputBuilder::getInstance() {
	if(outputBuilder==nullptr)
		switch(Options::globalOptions()->getOutputFormat()){
			case OUTPUT_TEXTUAL:
				outputBuilder=new TextualOutputBuilder;
				break;
			case OUTPUT_QUERY_TEXTUAL:
				outputBuilder=new QueryTextualOutputBuilder;
				break;
			default:
				outputBuilder=new NumericOutputBuilder;
				break;
		}

	return outputBuilder;
}

} /* namespace grounder */
} /* namespace DLV2 */
