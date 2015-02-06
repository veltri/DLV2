/*
 * Timer.h
 *
 *  Created on: Feb 6, 2015
 *      Author: davide
 */

#ifndef SRC_UTIL_TIMER_H_
#define SRC_UTIL_TIMER_H_

#include <unordered_map>
#include <string>
#include <time.h>

namespace DLV2 {
namespace grounder {

using namespace std;

class Timer {
public:
	Timer(){};
	virtual ~Timer(){};

	virtual void start(string label){
		auto it=map_time.find(label);
		if(it==map_time.)
	}
private:
	unordered_map<string,clock_t> map_time;
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_UTIL_TIMER_H_ */
