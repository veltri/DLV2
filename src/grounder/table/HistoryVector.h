/*
 * HistoryVector.h
 *
 *  Created on: Jan 18, 2016
 *      Author: davide
 */

#ifndef SRC_GROUNDER_TABLE_HISTORYVECTOR_H_
#define SRC_GROUNDER_TABLE_HISTORYVECTOR_H_

#include<vector>
#include "../../util/Assert.h"

using namespace std;

namespace DLV2 {
namespace grounder {

enum SearchType{ALL,OLD,NEW};


template<typename T>
class HistoryVector : public vector<T>{
public:
	using ElementsType = vector<T>;
	typedef typename std::vector<T>::iterator iterator;


	HistoryVector():current_iteration(0),index_iteration(0),index_previous_iteration(0){}

	HistoryVector(T& element,unsigned iteration):HistoryVector(){push_back(element,iteration);}

	inline void push_back_iteration(const T& element,unsigned iteration){
		if(current_iteration<iteration){
			current_iteration=iteration;
			index_previous_iteration=index_iteration;
			index_iteration=vector<T>::size();
		}
		vector<T>::push_back(element);
	}



	pair<unsigned,unsigned> getElements(SearchType type,unsigned iteration){
		if(iteration>current_iteration ){
			if(type==OLD)
				type=ALL;
			else if(type==NEW)
				return {0,0};

		}
		if(iteration<current_iteration && type==ALL){
			type=OLD;
			iteration=current_iteration;
		}


		unsigned index=(iteration==current_iteration)?index_iteration:index_previous_iteration;
		unsigned end=(iteration==current_iteration)?vector<T>::size():index_iteration;

		switch (type) {
			case ALL:
				return {0,vector<T>::size()};
				break;
			case OLD:
				return {0,index};
				break;
			case NEW:
				return {index,end};
				break;
			default:
				return {0,vector<T>::size()};
		}
	}


	inline unsigned size_iteration(SearchType type){
		switch (type) {
			case ALL:
				return vector<T>::size();
				break;
			case OLD:
				return index_iteration;
				break;
			case NEW:
				return vector<T>::size()-index_iteration;
				break;
			default:
				return vector<T>::size();
		}
	}


	inline unsigned getCurrentIteration(){
		return current_iteration;
	}

	inline unsigned getIndexIteration(){
		return index_iteration;
	}



private:
	unsigned current_iteration;
	unsigned index_iteration;
	unsigned index_previous_iteration;

};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_TABLE_HISTORYVECTOR_H_ */
