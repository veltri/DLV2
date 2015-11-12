/*
 * Rule.h
 *
 *  Created on: 03/apr/2014
 *      Author: Jessica
 */

#ifndef RULE_H_
#define RULE_H_

#include <vector>
#include <unordered_set>
#include "../atom/Atom.h"
#include "../hash/HashVecInt.h"

using namespace std;

namespace DLV2{

namespace grounder{

/**
 * @brief This class represents a rule with its body and head atoms
 */

class Rule : public Indexable {
public:
	Rule():Indexable(), ground(false), simplifiedHead(0), simplifiedBody(0), mustBeRewritedForAggregates(false)  {};
	Rule(bool g):Indexable(), ground(g), simplifiedHead(0), simplifiedBody(0), mustBeRewritedForAggregates(false) {};
	Rule(bool g, unsigned sizeHead, unsigned sizeBody) : Indexable(), ground(g), simplifiedHead(0), simplifiedBody(0), mustBeRewritedForAggregates(false) {
		if(ground){
			simplifiedHead=new bool[sizeHead];
			simplifiedBody=new bool[sizeBody];
			head.reserve(sizeHead);
			for(unsigned i=0;i<sizeHead;i++){
				simplifiedHead[i]=false;
				head.push_back(nullptr);
			}
			body.reserve(sizeBody);
			for(unsigned i=0;i<sizeBody;i++){
				simplifiedBody[i]=false;
				body.push_back(nullptr);
			}
		}
	};

	///Getter method for body atoms
	const vector<Atom*>& getBody() const {return body;}
	///Setter method for body atoms
	void setBody(const vector<Atom*>& body) {this->body = body;}
	///Getter method for head atoms
	const vector<Atom*>& getHead() const {return head;}
	///Setter method for head atoms
	void setHead(const vector<Atom*>& head) {this->head = head;}

	///This method returns true if it is a strong constrain
	bool isAStrongConstraint(){return head.empty();}
	///This method returns true if it is a fact
	bool isAFact(){return body.empty() && head.size()==1 && head[0]->isClassicalLiteral();}

	///This method adds an atom in the head
	void addInHead(Atom* a){head.push_back(a);};
	///This method adds an atom in the body
	void addInBody(Atom* a){body.push_back(a);};
	///This method adds a range of atoms in the body
	void addInBody(vector<Atom*>::iterator begin,vector<Atom*>::iterator end){body.insert(body.begin(),begin,end);};

	///This method returns the set of predicate in the head
	set_predicate getPredicateInHead(){return calculatePredicate(head,0,0);};
	///This method returns the set of predicate in the body
	set_predicate getPredicateInBody(){return calculatePredicate(body,0,0);};
	///This method returns the set of predicate of just the positive atoms in the body
	set_predicate getPositivePredicateInBody(){return calculatePredicate(body,1,0);};
	///This method returns the set of predicate index of just the positive atoms in the body
	unordered_set<index_object> getPositivePredicateIndexInBody(){return calculatePredicateIndex(body,1,0);};
	///This method returns the set of predicate of just the negative atoms in the body
	set_predicate getNegativePredicateInBody(){return calculatePredicate(body,1,1);};
	///This method returns the size of the head
	unsigned int getSizeHead() const {return head.size();}
	///This method return the size of the body
	unsigned int getSizeBody() const {return body.size();}
	///Remove atom in body
	void removeInBody(unsigned position){body.erase(body.begin()+position);};
	///Remove atoms in body
	///@position the index of the body atoms to remove from the vector
	void removeInBody(vector<unsigned>& position){
		sort(position.begin(),position.end());
		for(unsigned i=0;i<position.size();i++){body.erase(body.begin()+(position[i]-i));};
	};
	///Remove atom in body
	void removeInBody(vector<Atom*>::iterator it){body.erase(it);};
	///Insert an element in the body at specified position
	void insertInBody(Atom* atom,unsigned position){body.insert(body.begin()+position,atom);};

	///This method returns an iterator that points to the first atom in the body
	vector<Atom*>::iterator getBeginBody(){return body.begin();};
	vector<Atom*>::const_iterator getBeginBody()const{return body.begin();};
	///This method returns an iterator that points to the last atom in the body
	vector<Atom*>::const_iterator getEndBody()const{return body.end();};
	vector<Atom*>::iterator getEndBody(){return body.end();};
	///This method returns an iterator that points to the first atom in the head
	vector<Atom*>::const_iterator getBeginHead()const{return head.begin();};
	///This method returns an iterator that points to the last atom in the head
	vector<Atom*>::const_iterator getEndHead()const{return head.end();};

	///Return the specific atom in the body
	inline Atom* getAtomInBody(unsigned i) {return body[i];};
	///Set the specific atom in the body
	inline void setAtomInBody(unsigned i,Atom* atom) {body[i]=atom;};

	///Set the specific atom in the body
	inline void setAtomInHead(unsigned i,Atom* atom) {head[i]=atom;};
	///Return the specific atom in the head
	inline Atom* getAtomInHead(unsigned i) {return head[i];};

	///Set the simplification of the atom in the given position in the head
	void setAtomToSimplifyInHead(unsigned position, bool simplify = true){ simplifiedHead[position]=simplify;}
	///Set the simplification of the atom in the given position in the body
	void setAtomToSimplifyInBody(unsigned position, bool simplify = true){ simplifiedBody[position]=simplify;}
	///Get the simplification of the atom in the given position in the body
	bool isAtomToSimplifyInBody(unsigned position){return simplifiedBody[position];}

	///This method remove all the atoms in the body and in the head
	void clear(){head.clear();body.clear();};

	///Printer method
	void print(ostream& stream=cout);

	/** @brief Equal-to operator for rules
	 *  @details Two rules are equal if they have the same atoms in the body and in the head regardless the order in which they appear
	 */
	bool operator==(const Rule & r);

	///Destructor
	~Rule(){
		if(ground){
			delete[] simplifiedBody;
			delete[] simplifiedHead;
		}
	}

	bool isGround() const {return ground;}
	void setGround(bool ground) {this->ground=ground;}

	bool areThereUndefinedAtomInBody() const {for(unsigned i=0;i<body.size();i++) if(!simplifiedBody[i]) return true; return false;}

	///Getter and Setter to determine whether the rule contains at least an aggregate
	bool isMustBeRewritedForAggregates() const { return mustBeRewritedForAggregates; }
	void setMustBeRewritedForAggregates(bool mustBeRewritedForAggregates) {	this->mustBeRewritedForAggregates = mustBeRewritedForAggregates;}
	
	///Return true if is a choice rule
	bool isChoiceRule() const{ return (head.size()>0 && head[0]->isChoice());}

	void deleteBody(function<int(Atom*)> f);

	void deleteHead(function<int(Atom*)> f);

	void deleteGroundRule();

	void setUnsolvedPredicates();

	void sortPositiveLiteralInBody(vector<vector<unsigned>>& predicate_searchInsert_table);

private:

	/// Return the predicate in atoms vector, if checkNegative is true compare the negative of atom with the parameter
	/// else insert the predicate
	set_predicate calculatePredicate(vector<Atom*>& atoms,bool checkNegative,bool negative);
	/// Return the predicate index in atoms vector, if checkNegative is true compare the negative of atom with the parameter
	/// else insert the predicate
	unordered_set<index_object> calculatePredicateIndex(vector<Atom*>& atoms,bool checkNegative,bool negative);

	///Vector of the atoms in head
	vector<Atom*> head;
	///Vector of the atoms in body
	vector<Atom*> body;
	//Boolean to set whether the rule is ground
	bool ground;

	///An array containing true at a position in the head if that atom has to be simplified, false otherwise
	bool* simplifiedHead;
	///An array containing true at a position in the body if that atom has to be simplified, false otherwise
	bool* simplifiedBody;

	void printNonGround(ostream& stream=cout);

	bool mustBeRewritedForAggregates;
};


};

};
#endif /* RULE_H_ */
