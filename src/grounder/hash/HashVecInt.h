/*
 * HashVecInt.h
 *
 *  Created on: Jun 17, 2014
 *      Author: david
 */

#ifndef HASHVECINT_H_
#define HASHVECINT_H_

#include <vector>
#include <iostream>
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

	static void freeInstance(){ if(hashInt!=0) delete hashInt;}
	virtual ~HashVecInt(){}
	/// Return an HashVecInt according the configuration
	static HashVecInt* getHashVecInt();
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
		size_t seed=values[0]->getIndex();
		for(unsigned i=1;i<values.size();i++)
			boost::hash_combine(seed,values[i]->getIndex());
		return seed;
	}

};

/**
 *  Calculate the hash with boost combine method
 */
class GringoHashVecInt : public HashVecInt{
public:
	inline size_t computeHash(const vector<index_object> & values){
	    std::hash<index_object> hasher;
	    size_t seed=31;
		for(unsigned i=0;i<values.size();i++)
			seed ^= hasher(values[i]) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		return seed;
	}
	inline size_t computeHashSize_T(const vector<size_t> & values){
	    std::hash<index_object> hasher;
	    size_t seed=31;
		for(unsigned i=0;i<values.size();i++)
			seed ^= hasher(values[i]) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		return seed;
	}

	inline size_t computeHashTerm(const vector<Term*> & values){
	    std::hash<index_object> hasher;
	    size_t seed=31;
		for(unsigned i=0;i<values.size();i++)
			seed ^= hasher(values[i]->getIndex()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		return seed;
	}

};

class DLVHashVecInt : public HashVecInt{
public:
	inline size_t computeHash(const vector<index_object> & values){
	    size_t seed=values[0];
		for(unsigned i=1;i<values.size();i++)
			seed = seed*5+values[i];
		return seed;
	}
	inline size_t computeHashSize_T(const vector<size_t> & values){
	    size_t seed=values[0];
		for(unsigned i=1;i<values.size();i++)
			seed = seed*5+values[i];
		return seed;
	}

	inline size_t computeHashTerm(const vector<Term*> & values){
	    size_t seed=values[0]->getIndex();
		for(unsigned i=1;i<values.size();i++)
			seed = seed*5+values[i]->getIndex();
		return seed;
	}

};

};

};
#endif /* HASHVECINT_H_ */
