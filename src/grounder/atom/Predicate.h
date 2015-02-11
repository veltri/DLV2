/*
 * Predicate.h
 *
 *  Created on: 07/mar/2014
 *      Author: Jessica
 */

#ifndef PREDICATE_H_
#define PREDICATE_H_

#include <string>
#include <cstring>
#include "../hash/Hashable.h"
#include "../hash/HashVecInt.h"
#include "../hash/HashString.h"

using namespace std;

namespace DLV2{

namespace grounder{


class Predicate : public Hashable,public Indexable{
public:

	///Default constructor
	Predicate() : Indexable(), arity(0), edb(true) {};

	/** Constructor
	 * @param name set the name of the predicate
	 * @param arity set the arity of the predicate
	 */
	Predicate(string& name, unsigned int arity) : Indexable(), arity(arity), name(name), edb(true) {};

	/** Constructor
	 * @param name set the name of the predicate
	 * @param arity set the arity of the predicate
	 * @param edbIdb set whether the the predicate is an EDB or not
	 */
	Predicate(string& name, unsigned int arity, bool edbIdb) : Indexable(), arity(arity), name(name), edb(edbIdb) {};

	///Getter method for the arity
	unsigned int getArity() const {return arity;}
	///Setter method for the arity
	void setArity(unsigned int arity) {this->arity = arity;}
	///Getter method for the arity
	bool isEdb() const {return edb;}

	void setIdb() {this->edb=false;};

	void setEdb() {this->edb=true;};
	///Getter method for the name
	const string getName() const {return name;}
	///Setter method for the name
	void setName(const string& name) {this->name = name;}

	/// @brief Equal-to operator for predicates
	/// @details Two predicates are equal if they have the same name and the same arity
	bool operator==(Predicate &p)const{return p.getArity()==this->getArity() && strcmp(p.getName().c_str(),this->getName().c_str())==0;}

	size_t hash(){
		vector<size_t> hash_vec(2);
		hash_vec[0]=HashString::getHashString()->computeHash(name);
		hash_vec[1]=arity;
		return HashVecInt::getHashVecInt()->computeHashSize_T(hash_vec);
	}


	~Predicate(){};
private:
	///Arity
	unsigned int arity;
	///Name
	string name;
	///Whether it is EDB or IDB
	bool edb;
};


typedef unordered_set<Predicate*,IndexForTable<Predicate>,IndexForTable<Predicate>> set_predicate;

};

};

#endif /* PREDICATE_H_ */
