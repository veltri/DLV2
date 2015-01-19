/*
 * HashVecInt.cpp
 *
 *  Created on: Jun 17, 2014
 *      Author: david
 */

#include "HashVecInt.h"

namespace DLV2{

namespace grounder{

HashVecInt *HashVecInt::hashInt;

HashVecInt* HashVecInt::getHashVecIntFromConfig() {
	//TODO add selector

	return hashInt;
}


};

};
