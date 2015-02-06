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
#include <iostream>

namespace DLV2 {
namespace grounder {

using namespace std;

class Timer {
public:
	virtual ~Timer(){};

	void start(string label){
		clock_t clock_start=clock();
		auto it=map_clock.find(label);
		if(it==map_clock.end())
			map_clock.insert({label,clock_start});
		else{
			map_clock.erase(label);
			map_clock.insert({label,clock_start});
		}

	}

	void stop(string label){
		clock_t clock_end=clock();
		clock_t clock_start=map_clock[label];
		clock_t time_elapsed= clock_end - clock_start ;

		auto it=map_elapse_time.find(label);
		if(it==map_elapse_time.end())
			map_elapse_time.insert({label,time_elapsed});
		else{
			double previus_time=map_elapse_time[label];
			map_elapse_time.erase(label);
			map_elapse_time.insert({label,previus_time+time_elapsed});
		}
	}

	void print(){
		cout<<"TIME:"<<endl;
		for(auto& time_pair:map_elapse_time)
			cout<<time_pair.first<<" "<<(time_pair.second/ (double) CLOCKS_PER_SEC)<<endl;
	}

	void clear(){
		map_clock.clear();
		map_elapse_time.clear();
	}

	static Timer* getInstance(){
		if(timer_instance==nullptr)
			timer_instance=new Timer;
		return timer_instance;
	}

private:
	Timer(){};

	static Timer* timer_instance;



	unordered_map<string,clock_t> map_clock;
	unordered_map<string,clock_t> map_elapse_time;

};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_UTIL_TIMER_H_ */
