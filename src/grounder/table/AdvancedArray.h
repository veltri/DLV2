/*
 * AdvancedArray.h
 *
 */

#ifndef SRC_GROUNDER_TABLE_ADVANCEDARRAY_H_
#define SRC_GROUNDER_TABLE_ADVANCEDARRAY_H_

namespace DLV2 {
namespace grounder {

using namespace std;


template <typename T,unsigned S>
class AdvancedArray {
public:

	AdvancedArray():chooseStaticArray(true){}

	AdvancedArray(const AdvancedArray& array):chooseStaticArray(array.chooseStaticArray),dynamicArray(array.dynamicArray),staticArray(array.staticArray){};

	inline void setSize(unsigned size){
		if(size<S)
			chooseStaticArray=true;
		else{
			chooseStaticArray=false;
			dynamicArray.resize(size);
		}
	}

	inline void setSize(unsigned size,T element){
		if(size<S){
			chooseStaticArray=true;
			staticArray.fill(element);
		}else{
			chooseStaticArray=false;
			dynamicArray.resize(size,element);
		}
	}

	inline T& operator[](unsigned i){
		if(chooseStaticArray)
			return staticArray[i];
		return dynamicArray[i];
	}

	inline T operator[](unsigned i) const {
		if(chooseStaticArray)
			return staticArray[i];
		return dynamicArray[i];
	}

	inline unsigned size() const{
		if(chooseStaticArray)
			return S;
		return dynamicArray.size();
	}

	void fill(T element){
		if(chooseStaticArray)
			staticArray.fill(element);
		dynamicArray.assign(dynamicArray.size(),element);
	}

private:


	bool chooseStaticArray;
	array<T,S> staticArray;
	vector<T> dynamicArray;
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_TABLE_ADVANCEDARRAY_H_ */
