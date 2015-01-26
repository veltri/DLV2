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
		if(Options::globalOptions()->getHashType()==JAVA_HASH)
			hashInt = new JavaHashVecInt;
		else
			// Default select Java
			hashInt = new BoostCombineHashVecInt;
	}
	return hashInt;
}


};

};
