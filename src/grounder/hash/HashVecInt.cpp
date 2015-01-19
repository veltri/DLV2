/*
 * HashVecInt.cpp
 *
 *  Created on: Jun 17, 2014
 *      Author: david
 */

#include "HashVecInt.h"
#include "../../util/Options.h"

namespace DLV2{

namespace grounder{

HashVecInt *HashVecInt::hashInt;

HashVecInt* HashVecInt::getHashVecIntFromConfig() {
	if (hashInt == nullptr){
		if(Options::globalOptions()->getHashType()==BOOST_HASH)
			hashInt = new BoostCombineHashVecInt;
		else
			// Default select Java
			hashInt = new JavaHashVecInt;
	}
	return hashInt;
}


};

};
