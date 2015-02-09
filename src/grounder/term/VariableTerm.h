/*
 * VariableTerm.h
 *
 *  Created on: 25/feb/2014
 *      Author: Davide
 */

#ifndef VARIABLETERM_H_
#define VARIABLETERM_H_


#include "Term.h"
#include "../hash/HashString.h"

using namespace std;

namespace DLV2{

namespace grounder{

/*
 * Represent a term variable
 *
 * The variable is in IdsManager for avoiding duplication
 */
class VariableTerm: public Term {
public:
	VariableTerm():Term(),isAnonymous(0){};
	VariableTerm(bool negative):Term(negative),isAnonymous(0){};
	VariableTerm(bool negative,index_object index,string& name):Term(negative,index),name(name){setAnonymous();};
	VariableTerm(bool negative,string& name):Term(negative),name(name){setAnonymous();};

	virtual string getName()const{return name;};
	virtual void setName(const string& name){setAnonymous();};

	//Return the type of term
	virtual TermType getType()const{if(isAnonymous)return TermType::ANONYMOUS;return TermType::VARIABLE;};
	//Return true if contain a term of the given type
	virtual bool contain(TermType type){
		if(TermType::VARIABLE==type || (TermType::ANONYMOUS==type && isAnonymous))
			return true;
		return false;
	};


	virtual void getVariable(set_term& variables){if(!isAnonymous)variables.insert(this);};
	virtual size_t hash(){	return HashString::getHashString()->computeHash(name);};
	virtual Term* substitute(map_term_term& substitutionTerm){
		auto find_it=substitutionTerm.find(this);
		if(find_it!=substitutionTerm.end())
			return (*find_it).second;
		return this;
	};

	virtual void print(){
		cout<<name;
	}

private:
	void setAnonymous(){
		if(name.compare("_")==0)
			isAnonymous=true;
		else
			isAnonymous=false;
	}

	/**
	 *   The name of a variable
	 */
	string name;
	/*
	 *  True if is an anonymous variable ''_''
	 */
	bool isAnonymous;

};

};

};

#endif /* VARIABLETERM_H_ */
