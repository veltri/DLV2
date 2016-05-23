/*
 * SafetyExceptionGrounder.h
 *
 *  Created on: Mar 2, 2016
 *      Author: jessica
 */

#ifndef SRC_GROUNDER_EXCEPTION_SAFETYEXCEPTIONGROUNDER_H_
#define SRC_GROUNDER_EXCEPTION_SAFETYEXCEPTIONGROUNDER_H_

#include <exception>
#include "../statement/Rule.h"


namespace DLV2 {
namespace grounder {

using namespace std;

class SafetyExceptionGrounder : public exception {
public:
	SafetyExceptionGrounder() {}
	SafetyExceptionGrounder(string message) : msg(message) {}

	virtual const char* what() const throw(){
//		stringstream tmp;
//		rule->print(tmp);
//		return "This rule is not safe: "+tmp.str();
		return msg.c_str();
	}

private:
	string msg;
};

}}

#endif /* SRC_GROUNDER_EXCEPTION_SAFETYEXCEPTIONGROUNDER_H_ */
