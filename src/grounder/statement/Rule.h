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

///Tuple for the grounding part of the weak: Weight,Level, Terms (the label of the weak)
using tupleWeak = tuple<Term*,Term*,vector<Term*>>;

class Rule;


/**
 * This struct contain the information used for the match of atoms. Bound contain the index of term total bound. Bind the index of term
 * bind. Builtin the builtin atom that can be evaluated while we check the match of the atom. VarUsedInBuiltin the variable binded of the atom that we
 * match shared with one builtin in vector builtin. Other the functional atoms, arith term and variable binded in the atom that compare two times.
 **/
struct MatchInformation{
	vector<unsigned> bound;
	//CAN BE OPTIMIZED with vector<unisnged>
	vector<pair<unsigned,unsigned>> bind;
	vector<pair<unsigned,unsigned>> varUsedInBuiltin;
	vector<Atom*> builtin;
	vector<unsigned> other;
	vector<unsigned> dictionaryIntersection;
};

///RuleInformation contain the information of rule relative:
///		- The number of the variable in the body of the rule
///		- The intersection of the dictionary for each positive classical literal
class RuleInformation{

public:

	set_term::const_iterator getDictionaryIntersectionBegin(index_object index)const{
		return dictionaryIntersection[index].begin();
	}
	set_term::const_iterator getDictionaryIntersectionEnd(index_object index)const{
		return dictionaryIntersection[index].end();
	}

	set_term::iterator getDictionaryIntersectionBegin(index_object index){
		return dictionaryIntersection[index].begin();
	}
	set_term::iterator getDictionaryIntersectionEnd(index_object index){
		return dictionaryIntersection[index].end();
	}

	void removeInDictionaryIntersection(set_term::iterator& it,index_object index){
		it=dictionaryIntersection[index].erase(it);
	}

	void insertInDictionaryIntersection(index_object index,Term* term){
		dictionaryIntersection[index].insert(term);
		dictionaryIntersectionCreation[index]=true;
	}

	void insertInDictionaryIntersection(index_object index,const set_term& set){
		dictionaryIntersection[index].insert(set.begin(),set.end());
		dictionaryIntersectionCreation[index]=true;
	}

	void setDictionaryIntersectionSize(unsigned size){
		dictionaryIntersection.resize(size);
		dictionaryIntersectionCreation.resize(size,false);
	}

	void clearDictionaryIntersection(){
		dictionaryIntersection.clear();
		dictionaryIntersectionCreation.clear();
	}

	inline bool countInDictionaryIntersection(index_object index,Term* term)const{
		return dictionaryIntersection[index].count(term);
	}

	inline unsigned getDictionaryIntersectionSize(index_object index)const{
		return dictionaryIntersection[index].size();
	}


	inline bool isCreatedDictionaryIntersection(index_object index)const{
		if(index>=dictionaryIntersectionCreation.size())
			return false;
		return dictionaryIntersectionCreation[index];
	}

	inline void addBounderBuiltin(unsigned i,Atom *builtin){
		if(i>=bounderBuiltins.size())
			bounderBuiltins.resize(i+1);
		bounderBuiltins[i].push_back(builtin);
	}

	inline void clearBounderBuiltin(){
		bounderBuiltins.clear();
	}

	inline const vector<Atom*>& getBounderBuiltin(unsigned i)const{
		return bounderBuiltins[i];
	}

	inline bool isBounderBuiltin(unsigned i)const{
		if(i>=bounderBuiltins.size() || bounderBuiltins[i].empty())
			return false;
		return true;
	}


	void print()const{
		cerr<<"Dictionary Intersection"<<endl;
		for(unsigned i=0;i<dictionaryIntersectionCreation.size();++i){
			if(dictionaryIntersectionCreation[i]){
				for(auto t:joinVariables)
					if(t->getLocalVariableIndex()==i)
					{
						t->print(cerr);cerr<<" --> ";
						break;
					}
				for(auto t:dictionaryIntersection[i]){
					t->print(cerr);cerr<<" ";
				}
				cerr<<endl;
			}
		}
	}

	void insertJoinVariable(Term* term) {joinVariables.insert(term);}

	bool isAJoinVariable(Term* term) const {return joinVariables.count(term);}

	void computeOutputVariables(Rule* rule);

	bool isAnOutputVariable(Term* term, Rule* rule){
		if(outputVariables.empty())
			computeOutputVariables(rule);
		return outputVariables.count(term);
	}

	set_term& getOutputVariables(Rule* rule){
		if(outputVariables.empty())
			computeOutputVariables(rule);
		return outputVariables;
	}

	const MatchInformation& getMatchInformation(unsigned indexAtom,unsigned subAtom=0)const{
		return atomMatchInformation[indexAtom][subAtom];
	}

	void addMatchInformation(MatchInformation& matchInfo,unsigned indexAtom){
		atomMatchInformation[indexAtom].push_back(matchInfo);
	}

	void clearAndResizeMatchInfo(unsigned size){
		atomMatchInformation.clear();
		atomMatchInformation.resize(size);
	}

private:
	vector<set_term> dictionaryIntersection;
	vector<bool> dictionaryIntersectionCreation;
	set_term joinVariables;
	vector<vector<Atom*>> bounderBuiltins;
	/// The set of variables appearing in the head of the current rule
	set_term outputVariables;
	/// For each atom a vector of match information. If is classical literal the vector contain exactly one matchInformation, if is
	/// an aggregate atom contain a matchInformation for each aggregate element
	vector<vector<MatchInformation>> atomMatchInformation;
};



/**
 * @brief This class represents a rule with its body and head atoms
 */

class Rule : public Indexable {
public:
	Rule():Indexable(), ground(false), simplifiedHead(0), simplifiedBody(0), mustBeRewritedForAggregates(false),variablesSize(0)  {};
	Rule(bool g):Indexable(), ground(g), simplifiedHead(0), simplifiedBody(0), mustBeRewritedForAggregates(false),variablesSize(0) {};
	Rule(bool g, unsigned sizeHead, unsigned sizeBody) : Indexable(), ground(g), simplifiedHead(0), simplifiedBody(0), mustBeRewritedForAggregates(false),variablesSize(0) {
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
	virtual bool isAStrongConstraint(){return head.empty();}
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
	///@positions the index of the body atoms to remove from the vector
	/// WARNING: POSITIONS MUST BE ORDERED
	void removeInBody(vector<unsigned>& positions){for(unsigned i=0;i<positions.size();i++){body.erase(body.begin()+(positions[i]-i));}}
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
	virtual void print(ostream& stream=cout);

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
	bool isChoiceRule() const{ return (head.size()==1 && head[0]->isChoice());}

	void deleteBody(function<int(Atom*)> f);

	void deleteHead(function<int(Atom*)> f);

	void deleteGroundRule();

	void setUnsolvedPredicates();

	void sortPositiveLiteralInBody(vector<vector<unsigned>>& predicate_searchInsert_table,vector<unsigned>& originalOrderMapping);

	void computeVariablesLocalIndices();

	inline unsigned getVariablesSize() const {
		return variablesSize;
	}

	virtual bool isWeakConstraint(){
		return false;
	}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
	virtual const vector<Term*>& getLabel() const {}
#pragma GCC diagnostic pop
	virtual unsigned getLevelInt(){return 0;}
	virtual Term* getLevel() const {	return nullptr;}
	virtual Term* getWeight() const {return nullptr;}
	virtual void setWeightLevelLabel(tupleWeak&& tp){};
	virtual tupleWeak groundWeightLevel(var_assignment& current_assignment){return make_tuple(nullptr,nullptr,vector<Term*>());}

	//-----------------Rule Information Interface -------------------------------

	set_term::const_iterator getDictionaryIntersectionBegin(index_object index) const {
		return ruleInformation.getDictionaryIntersectionBegin(index);
	}
	set_term::const_iterator  getDictionaryIntersectionEnd(index_object index) const{
		return ruleInformation.getDictionaryIntersectionEnd(index);
	}

	set_term::iterator getDictionaryIntersectionBegin(index_object index) {
		return ruleInformation.getDictionaryIntersectionBegin(index);
	}
	set_term::iterator  getDictionaryIntersectionEnd(index_object index) {
		return ruleInformation.getDictionaryIntersectionEnd(index);
	}

	void removeInDictionaryIntersection(set_term::iterator& it,index_object index){
		ruleInformation.removeInDictionaryIntersection(it,index);
	}

	const RuleInformation& getRuleInformation(){
		return ruleInformation;
	}

	void insertInDictionaryIntersection(index_object index,Term* term){
		ruleInformation.insertInDictionaryIntersection(index,term);
	}

	void insertInDictionaryIntersection(index_object index,const set_term& set){
		ruleInformation.insertInDictionaryIntersection(index,set);
	}

	void setDictionaryIntersectionSize(unsigned size){
		ruleInformation.setDictionaryIntersectionSize(size);
	}

	void clearDictionaryIntersection(){
		ruleInformation.clearDictionaryIntersection();
	}

	inline void addBounderBuiltin(unsigned i,Atom *builtin){
		ruleInformation.addBounderBuiltin(i,builtin);
	}

	inline void clearBounderBuiltin(){
		ruleInformation.clearBounderBuiltin();
	}

	bool isAnOutputVariable(Term* term){
		return ruleInformation.isAnOutputVariable(term,this);
	}

	set_term& getOutputVariables() {
		return ruleInformation.getOutputVariables(this);
	}

	void addMatchInformation(MatchInformation& matchInfo,unsigned indexAtom){
		ruleInformation.addMatchInformation(matchInfo,indexAtom);
	}

	void clearAndResizeMatchInfo(unsigned size){
		ruleInformation.clearAndResizeMatchInfo(size);
	}

protected:

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

	virtual void printNonGround(ostream& stream=cout);

	bool mustBeRewritedForAggregates;

	RuleInformation ruleInformation;

	unsigned variablesSize;

};



class WeakConstraint : public Rule{
public:


	WeakConstraint():weight(nullptr),level(nullptr),levelInt(0){}

	WeakConstraint(const vector<Atom*>& body,Term* weight, Term* level,const vector<Term*>& terms):weight(weight),level((level==nullptr)?TermTable::getInstance()->term_zero:level),label(terms),levelInt(0){
		this->body=body;
	}

	WeakConstraint(bool g, unsigned sizeBody,const vector<Atom*>& body,Term* weight, Term* level,const vector<Term*>& terms):Rule(g,0,sizeBody),weight(weight),level((level==nullptr)?TermTable::getInstance()->term_zero:level),label(terms),levelInt((g)?level->getConstantValue():0){
		this->body=body;
	}

	WeakConstraint(bool g, unsigned sizeBody,Term* weight, Term* level,const vector<Term*>& terms):Rule(g,0,sizeBody),weight(weight),level((level==nullptr)?TermTable::getInstance()->term_zero:level),label(terms),levelInt((g)?level->getConstantValue():0){
	}

	virtual bool isWeakConstraint(){return true;}

	const vector<Term*>& getLabel() const {return label;}

	void setLabel(const vector<Term*>& label) {	this->label = move(label);}

	Term* getLevel() const {	return level;}

	unsigned getLevelInt(){return levelInt;}

	void setLevel(Term* level) {	this->level = level;}

	Term* getWeight() const {return weight;}

	void setWeight(Term* weight) {this->weight = weight;}

	virtual void print(ostream& stream=cout);

	bool isAStrongConstraint(){return false;}

	void printNonGround(ostream& stream=cout);

	virtual void setWeightLevelLabel(tupleWeak&& groundWeightLevelLabel){
		weight=get<0>(groundWeightLevelLabel);
		level=get<1>(groundWeightLevelLabel);
		label=move(get<2>(groundWeightLevelLabel));
	};


	///Ground the Weight, the level and the label of the weak and return with the tuple
	tupleWeak groundWeightLevel(var_assignment& current_assignment);

private:
	Term* weight;
	Term* level;

	vector<Term*> label;

	unsigned levelInt;
};


};

};
#endif /* RULE_H_ */
