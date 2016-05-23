/*
 * VecStack.h
 *
 *  Created on: May 10, 2016
 *      Author: davide
 */

#ifndef SRC_UTIL_VECSTACK_H_
#define SRC_UTIL_VECSTACK_H_

#include <vector>

using namespace std;

namespace DLV2 {

template<typename T>
struct VecStack {
	VecStack():topIndex(0){};
	void reserve(unsigned s){vec.reserve(s);};
	T& pop(){
		--topIndex;
		return vec[topIndex];
	}
	void push(T t){
		if(topIndex==vec.size())
			vec.push_back(t);
		else
			vec[topIndex]=t;
		topIndex++;
	}

	vector<T> vec;
	unsigned topIndex;
};

} /* namespace DLV2 */

#endif /* SRC_UTIL_VECSTACK_H_ */
