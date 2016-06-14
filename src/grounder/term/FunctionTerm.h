/*
 * FunctionTerm.h
 *
 *  Created on: 25/feb/2014
 *      Author: Davide
 */

#ifndef FUNCTIONTERM_H_
#define FUNCTIONTERM_H_


#include "Term.h"

#include "../table/TermTable.h"


using namespace std;

namespace DLV2{

namespace grounder{

/*
 *  Represent a functional term.
 */
class FunctionTerm: public Term {
public:
	FunctionTerm(string& name,bool negative):Term(negative),name(name){};
	FunctionTerm(string& v,bool negative,vector<Term*>& terms):Term(negative),name(v),terms(terms){};
	FunctionTerm(string& v,index_object index):name(v){setIndex(index);};
	FunctionTerm(string& v,index_object index,vector<Term*>& terms):name(v),terms(terms){setIndex(index);};

	virtual string getName()const{return name;};
	virtual void setName(string& name){this->name=name;};

	virtual unsigned getTermsSize()const{return terms.size();}
	virtual Term* getTerm(unsigned i)const{return terms[i];}

	virtual void addTerm(Term* term){terms.push_back(term);};
	virtual void popTerm(){terms.pop_back();};


	virtual TermType getType()const{return TermType::FUNCTION;};
	virtual bool contain(TermType type){
		if(type==TermType::FUNCTION) return true;
		for(auto term:terms)
			if(term->contain(type))
				return true;
		return false;
	}
	virtual bool isGround(){
		for(auto term:terms)
			if(!term->isGround())
				return false;
		return true;
	}


	virtual void getVariable(set_term& variables){
		for(auto term:terms)
			term->getVariable(variables);
	};

	virtual void getVariable(vector<Term*>& variables){
		for(auto term:terms)
			term->getVariable(variables);
	};

	virtual void getGroundTerm(set_term& variables){
		for(auto term:terms)
			term->getGroundTerm(variables);
	};

	vector<Term*>& getTerms(){return terms;};


	virtual bool operator==(const Term& term) const;

	virtual bool operator>(const Term& term)const;
	virtual bool operator>=(const Term& term)const;

	virtual bool operator<(const Term& term)const;
	virtual bool operator<=(const Term& term)const;

	virtual Term* calculate();
	virtual Term* substitute(var_assignment& substitutionTerm);
	/// Return the name of the function concatenated with '*' and the id of the composites term
	virtual size_t hash();

	virtual void print(ostream& stream=cout);

	virtual void getVariablesInArith(set_term& vars){
		for(auto t:terms)
			t->getVariablesInArith(vars);
	}

	virtual void substitute(Term* t,Term* t1){
		for(unsigned i=0;i<terms.size();++i){
			if(t->getIndex()==terms[i]->getIndex())
				terms[i]=t1;
			else if(terms[i]->contain(TermType::FUNCTION)){
				terms[i]->substitute(t,t1);
			}
		}
	}

private:
	/**
	 *   The name of a function
	 */
	string name;

	/**
	 *  All the index of the terms inside the function
	*/
	vector<Term*> terms;
};

};

};

#endif /* FUNCTIONTERM_H_ */
