/*
 * HashVecInt.h
 *
 *  Created on: Jun 17, 2014
 *      Author: david
 */

#ifndef HASHVECINT_H_
#define HASHVECINT_H_

#include <vector>

#include <boost/functional/hash.hpp>

#include "../../util/Constants.h"
#include "Hashable.h"
#include "../term/Term.h"

using namespace std;


namespace DLV2{

namespace grounder{

/**
 *  Calculate the hash of a vector of integers
 */
class HashVecInt {
public:
	HashVecInt(){};
	/// Calculate the hash of a vector of index_object
	virtual size_t computeHash(const vector<index_object>& values)=0;
	/// Calculate the hash of a vector of size_t
	virtual size_t computeHashSize_T(const vector<size_t>& values)=0;
	/// Calculate the hash of a vector of size_t
	virtual size_t computeHashTerm(const vector<Term*>& values)=0 ;


	virtual ~HashVecInt(){delete hashInt;};
	/// Return an HashVecInt according the configuration
	static HashVecInt* getHashVecIntFromConfig();
private:
	static HashVecInt *hashInt;
};

/**
 *  Calculate the hash with java method
 */
class JavaHashVecInt : public HashVecInt{
public:
	JavaHashVecInt(){}
	inline size_t computeHash(const vector<index_object> &values){
		int length=values.size();
		size_t hash=0;
		for (int i = 0; i < length; i++) {
			hash+=values[i]*pow(31.0,length-(i));
		}

		return hash;
	}
	inline size_t computeHashSize_T(const vector<size_t> &values){
		int length=values.size();
		size_t hash=0;
		for (int i = 0; i < length; i++) {
			hash+=values[i]*pow(31.0,length-(i));
		}

		return hash;
	}

	inline size_t computeHashTerm(const vector<Term*> &values){
		int length=values.size();
		size_t hash=0;
		for (int i = 0; i < length; i++) {
			hash+=values[i]->getIndex()*pow(31.0,length-(i));
		}

		return hash;
	}

};

/**
 *  Calculate the hash with boost combine method
 */
class BoostCombineHashVecInt : public HashVecInt{
public:
	inline size_t computeHash(const vector<index_object> & values){
		return boost::hash_range(values.begin(),values.end());
	}
	inline size_t computeHashSize_T(const vector<size_t> & values){
		return boost::hash_range(values.begin(),values.end());
	}

	inline size_t computeHashTerm(const vector<Term*> & values){
		vector<size_t> size_t_values(values.size());
		for(unsigned i=0;i<values.size();i++)
			size_t_values[i]=values[i]->getIndex();
		return computeHashSize_T(size_t_values);
	}

};


};

};
#endif /* HASHVECINT_H_ */