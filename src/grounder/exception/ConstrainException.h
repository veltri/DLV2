/*
 * ConstrainException.h
 *
 *  Created on: Jul 21, 2015
 *      Author: davide
 */

#ifndef SRC_GROUNDER_EXCEPTION_CONSTRAINEXCEPTION_H_
#define SRC_GROUNDER_EXCEPTION_CONSTRAINEXCEPTION_H_

#include <exception>

namespace DLV2 {
namespace grounder {

using namespace std;

class ConstrainException:public exception {
public:
	ConstrainException(){};
	virtual const char* what() const throw(){
		return "";
	}
} ;

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_EXCEPTION_CONSTRAINEXCEPTION_H_ */
