/*
 * RangeTerm.h
 *
 *  Created on: 08/feb/2015
 *      Author: tesi2
 */

#ifndef RANGETERM_H_
#define RANGETERM_H_

#include "Term.h"

namespace DLV2{

namespace grounder{

class RangeTerm: public DLV2::grounder::Term {
public:
	RangeTerm():Term(),lowerBound(0),upperBound(0){}
	RangeTerm(int l, int u):Term(),lowerBound(l),upperBound(u){}

	virtual bool isRange() const {return true;}

	int getLowerBound() const {return lowerBound;}
	void setLowerBound(int lowerBound) {this->lowerBound = lowerBound;}

	int getUpperBound() const {return upperBound;}
	void setUpperBound(int upperBound) {this->upperBound = upperBound;}
private:
	int lowerBound;
	int upperBound;
};

}

}

#endif /* RANGETERM_H_ */
