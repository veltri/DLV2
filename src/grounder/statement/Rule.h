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
	Rule():Indexable(), ground(false) {};
	Rule(bool g):Indexable(), ground(g) {};
	Rule(bool g, unsigned sizeHead, unsigned sizeBody) : Indexable(), ground(g) {
		head.reserve(sizeHead);
		for(unsigned i=0;i<sizeHead;i++)
			head.push_back(nullptr);
		body.reserve(sizeBody);
		for(unsigned i=0;i<sizeBody;i++)
			body.push_back(nullptr);
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
	bool isAFact(){return body.empty() && head.size()==1;}

	///This method adds an atom in the head
	void addInHead(Atom* a){head.push_back(a);};
	///This method adds an atom in the body
	void addInBody(Atom* a){body.push_back(a);};
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
	///Insert an element in the body at specified position
	void insertInBody(Atom* atom,unsigned position){body.insert(body.begin()+position,atom);};

	///This method returns an iterator that points to the first atom in the body
	vector<Atom*>::iterator getBeginBody(){return body.begin();};
	vector<Atom*>::const_iterator getBeginBody()const{return body.begin();};
	///This method returns an iterator that points to the last atom in the body
	vector<Atom*>::const_iterator getEndBody()const{return body.end();};
	///This method returns an iterator that points to the first atom in the head
	vector<Atom*>::const_iterator getBeginHead()const{return head.begin();};
	///This method returns an iterator that points to the last atom in the head
	vector<Atom*>::const_iterator getEndHead()const{return head.end();};

	///Order builtin and negative atom in the rule
	void basicSortBody();

	///Return the specific atom in the body
	Atom* getAtomInBody(unsigned i) {return body[i];};
	///Set the specific atom in the body
	void setAtomInBody(unsigned i,Atom* atom) {body[i]=atom;};

	///This method remove all the atoms in the body and in the head
	void clear(){head.clear();body.clear();};

	bool isSafe();

	///Printer method
	void print();

	/** @brief Equal-to operator for rules
	 *  @details Two rules are equal if they have the same atoms in the body and in the head regardless the order in which they appear
	 */
	bool operator==(const Rule & r);

	///Destructor
	~Rule(){
		//The delete policy differs when the rule is not ground
		if(!ground){
			for(auto atom:head)
				delete atom;
			for(auto atom:body)
				delete atom;
		}
	}

	bool isGround() const;
	void setGround(bool ground);

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
};


};

};
#endif /* RULE_H_ */
