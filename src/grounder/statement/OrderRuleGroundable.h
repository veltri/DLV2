/*
 * OrderRuleGroundable.h
 *
 *  Created on: Nov 25, 2015
 *      Author: jessica
 */

#ifndef SRC_GROUNDER_STATEMENT_ORDERRULEGROUNDABLE_H_
#define SRC_GROUNDER_STATEMENT_ORDERRULEGROUNDABLE_H_

#include <list>
#include "Rule.h"
#include "../table/PredicateExtension.h"


namespace DLV2 {
namespace grounder {

struct Priority{
	Priority(double bP, double n, double builtIn, double defAggAssign, double defAggNoAssign, double undefAggAssign, double undefAggNoAssign):
		BOUND_POSITIVE_CLASSICAL_LIT(bP),NEGATIVE_CLASSICAL_LIT(n),BUILT_IN(builtIn),DEFINED_AGGREGATE_NO_ASSIGNMENT(defAggAssign),
		DEFINED_AGGREGATE_ASSIGNMENT(defAggNoAssign),UNDEFINED_AGGREGATE_NO_ASSIGNMENT(undefAggAssign),
		UNDEFINED_AGGREGATE_ASSIGNMENT(undefAggNoAssign){}

	Priority():
		BOUND_POSITIVE_CLASSICAL_LIT(-5),NEGATIVE_CLASSICAL_LIT(-5),BUILT_IN(-6),DEFINED_AGGREGATE_NO_ASSIGNMENT(-3),
		DEFINED_AGGREGATE_ASSIGNMENT(-4),UNDEFINED_AGGREGATE_NO_ASSIGNMENT(-1),
		UNDEFINED_AGGREGATE_ASSIGNMENT(-2){}

	const double BOUND_POSITIVE_CLASSICAL_LIT;
	const double NEGATIVE_CLASSICAL_LIT;
	const double BUILT_IN;
	const double DEFINED_AGGREGATE_NO_ASSIGNMENT;
	const double DEFINED_AGGREGATE_ASSIGNMENT;
	const double UNDEFINED_AGGREGATE_NO_ASSIGNMENT;
	const double UNDEFINED_AGGREGATE_ASSIGNMENT;
};

class OrderRuleGroundable {
public:
	OrderRuleGroundable(Rule* rule):predicateExtTable(PredicateExtTable::getInstance()),rule(rule),componentPredicateInHead(0){}
	OrderRuleGroundable(Rule* rule, Priority p):predicateExtTable(PredicateExtTable::getInstance()),rule(rule),priorities(p),componentPredicateInHead(0){}
	virtual ~OrderRuleGroundable(){}
	///This method orders the body of a given exit rule
	vector<unsigned> order(vector<vector<pair<unsigned,SearchType>>>& predicate_searchInsert_table, vector<vector<IndexingStructure*>>& predicate_searchInsert_atomSearcher, unordered_set<index_object>* componentPredicateInHead=0);
	///This method orders the body of a given recursive rule
	void order(vector<vector<pair<unsigned,SearchType>>>& predicate_searchInsert_table,vector<vector<IndexingStructure*>>& predicate_searchInsert_atomSearcher, vector<unsigned>& originalOrderBody, unordered_set<index_object>* componentPredicateInHead=0);

	/// This method assigns to each remained atom (to be added in the sorted body) a weight,
	/// and returns the iterator to the atom with the best weight.
	/// It is virtual pure, because it has to be defined in each concrete class.
	virtual list<unsigned>::iterator assignWeights(list<unsigned>& atomsToInsert) = 0;

	virtual bool isBound(Atom* atom, unsigned orginalPosition,const set_term& terms);


protected:
	vector<vector<pair<unsigned,SearchType>>> predicate_searchInsert_table;
	PredicateExtTable* predicateExtTable;
	Rule* rule;
	set_term variablesInTheBody;
	vector<set_term> atomsVariables;
	const Priority priorities;
	list<unsigned> atomsToInsert;
	/// A map in which for each positive classical literal are stored variables that must be bound
	/// (for example variables appearing in arith terms)
	unordered_map<unsigned,set_term> mapPositiveAtomsBoundVariables;

	/// For each predicate in the current rule this vector stores the atom searchers of insertion and look-up for head atoms and
	/// the atom searchers of look-up for body atoms
	vector<vector<IndexingStructure*>> predicate_searchInsert_atomSearcher;

	//Set of recursive predicates
	unordered_set<index_object>* componentPredicateInHead;

	void computeDictionaryIntersection(Atom* atom);
	virtual bool setAtomSearcher(Atom* atom, unsigned orginalPosition){return false;};

private:
	void applyBinderSplittingRewriting();
};

class AllOrderRuleGroundable : public OrderRuleGroundable{
public:
	AllOrderRuleGroundable(Rule* rule):OrderRuleGroundable(rule){}
	AllOrderRuleGroundable(Rule* rule, Priority p):OrderRuleGroundable(rule,p){}
	virtual ~AllOrderRuleGroundable(){}
	virtual list<unsigned>::iterator assignWeights(list<unsigned>& atomsToInsert);

	virtual double assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition){return 0;};
	virtual double assignWeightBoundPositiveClassicalLit(Atom* atom, unsigned originalPosition){return priorities.BOUND_POSITIVE_CLASSICAL_LIT;};
	virtual double assignWeightNegativeClassicalLit(Atom* atom, unsigned originalPosition){return priorities.NEGATIVE_CLASSICAL_LIT;};
	//TODO check aggregate type
	virtual double assignWeightAggregateAtom(Atom* atom, unsigned originalPosition){return priorities.UNDEFINED_AGGREGATE_ASSIGNMENT;};
	virtual double assignWeightBuiltInAtom(Atom* atom, unsigned originalPosition){return priorities.BUILT_IN;};
	virtual void update(Atom* atomAdded, unsigned originalPosition){};
	virtual double manageEqualWeights(unsigned originalPosition);
	virtual bool ckeckSimilarity(double weight1,double weight2){return weight1==weight2;};

private:
	unsigned computePredicateExtensionSize(unsigned atomPosition, Predicate* p);
};

class CombinedCriterion : public AllOrderRuleGroundable {
public:
	CombinedCriterion(Rule* rule):AllOrderRuleGroundable(rule),DOUBLE_INDEX_THRESHOLD(0.3){positiveAtomsIndexingTerms.resize(rule->getSizeBody());}
	CombinedCriterion(Rule* rule,Priority p):AllOrderRuleGroundable(rule,p),DOUBLE_INDEX_THRESHOLD(0.3){positiveAtomsIndexingTerms.resize(rule->getSizeBody());}
	virtual ~CombinedCriterion(){}
	virtual double assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition);
	virtual void update(Atom* atomAdded, unsigned originalPosition){updateVariableSelectivity(atomAdded);};
	virtual bool setAtomSearcher(Atom* atom, unsigned orginalPosition);
protected:
	void computeVariablesDomains();
	void updateVariableSelectivity(Atom* atomAdded);
	map_term<unsigned> variablesDomains;
	map_term<double> variablesSelectivities;

	double computeBestIndexingTerms(Atom* atom, unsigned originalPosition);
	void computeBoundArgumentsSelectivities();
	vector<unordered_map<unsigned,double>> boundArgumentsSelectivities;
	const double DOUBLE_INDEX_THRESHOLD;
	vector<vector<set_term>> variablesInTerms;
	vector<vector<unsigned>> positiveAtomsIndexingTerms;

	double computeBoundAtoms(Atom* atom, unsigned originalPosition);
	double computeOutputVariablesBounded(Atom* atom, unsigned originalPosition);

};

class CombinedCriterion1 : public CombinedCriterion {
public:
	CombinedCriterion1(Rule* rule):CombinedCriterion(rule){}
	CombinedCriterion1(Rule* rule,Priority p):CombinedCriterion(rule,p){}
	virtual ~CombinedCriterion1(){}
	virtual double assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition);
};

class CombinedCriterion3 : public CombinedCriterion {
public:
	CombinedCriterion3(Rule* rule):CombinedCriterion(rule){}
	CombinedCriterion3(Rule* rule,Priority p):CombinedCriterion(rule,p){}
	virtual ~CombinedCriterion3(){}
	virtual double assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition);
};

class CombinedCriterion4 : public CombinedCriterion {
public:
	CombinedCriterion4(Rule* rule):CombinedCriterion(rule){}
	CombinedCriterion4(Rule* rule,Priority p):CombinedCriterion(rule,p){}
	virtual ~CombinedCriterion4(){}
	virtual double assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition);
};

class IndexingArgumentsOrderRuleGroundable  : public AllOrderRuleGroundable{
public:
	IndexingArgumentsOrderRuleGroundable(Rule* rule):AllOrderRuleGroundable(rule),DOUBLE_INDEX_THRESHOLD(0.3),currentJoinSize(1){}
	IndexingArgumentsOrderRuleGroundable(Rule* rule,Priority p):AllOrderRuleGroundable(rule,p),DOUBLE_INDEX_THRESHOLD(0.3),currentJoinSize(1){}
	virtual ~IndexingArgumentsOrderRuleGroundable(){}
	virtual double assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition);
	virtual void update(Atom* atomAdded, unsigned originalPosition);
//	virtual double manageEqualWeights(unsigned originalPosition);

private:
	void computeBoundArgumentsSelectivities();
	vector<unordered_map<unsigned,double>> boundArgumentsSelectivities;
	vector<vector<set_term>> variablesInTerms;
	const double DOUBLE_INDEX_THRESHOLD;
	double currentJoinSize;
	vector<unsigned> backwardWeights;
};


class SemiJoinIndexingArgumentsOrderRuleGroundable  : public CombinedCriterion{
public:
	SemiJoinIndexingArgumentsOrderRuleGroundable(Rule* rule):CombinedCriterion(rule),DOUBLE_INDEX_THRESHOLD(0.3){}
	SemiJoinIndexingArgumentsOrderRuleGroundable(Rule* rule,Priority p):CombinedCriterion(rule,p),DOUBLE_INDEX_THRESHOLD(0.3){}
	virtual ~SemiJoinIndexingArgumentsOrderRuleGroundable(){}
	virtual double assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition);
protected:
	vector<unordered_map<unsigned,double>> boundArgumentsSelectivities;
	const double DOUBLE_INDEX_THRESHOLD;
	vector<vector<set_term>> variablesInTerms;
};

class SemiJoinIndexingArgumentsOrderRuleGroundable2  : public SemiJoinIndexingArgumentsOrderRuleGroundable{
public:
	SemiJoinIndexingArgumentsOrderRuleGroundable2(Rule* rule):SemiJoinIndexingArgumentsOrderRuleGroundable(rule),SIMILARITY_THRESHOLD(0.3){}
	SemiJoinIndexingArgumentsOrderRuleGroundable2(Rule* rule,Priority p):SemiJoinIndexingArgumentsOrderRuleGroundable(rule,p),SIMILARITY_THRESHOLD(0.3){}
	virtual ~SemiJoinIndexingArgumentsOrderRuleGroundable2(){}
	virtual double assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition);
	virtual double manageEqualWeights(unsigned originalPosition);
	virtual bool ckeckSimilarity(double weight1,double weight2);
private:
	const double SIMILARITY_THRESHOLD;
};

class CombinedCriterionIndexingArgumentsOrderRuleGroundable  : public SemiJoinIndexingArgumentsOrderRuleGroundable {
public:
	CombinedCriterionIndexingArgumentsOrderRuleGroundable(Rule* rule):SemiJoinIndexingArgumentsOrderRuleGroundable(rule){}
	CombinedCriterionIndexingArgumentsOrderRuleGroundable(Rule* rule,Priority p):SemiJoinIndexingArgumentsOrderRuleGroundable(rule,p){}
	virtual ~CombinedCriterionIndexingArgumentsOrderRuleGroundable(){}
	virtual double assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition);
};

class BindersOrderRuleGroundable : public AllOrderRuleGroundable {
public:
	BindersOrderRuleGroundable(Rule* rule):AllOrderRuleGroundable(rule){}
	BindersOrderRuleGroundable(Rule* rule,Priority p):AllOrderRuleGroundable(rule,p){}
	virtual ~BindersOrderRuleGroundable(){}
	virtual double assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition);
};

class CombinedCriterionBindersOrderRuleGroundable: public CombinedCriterion {
public:
	CombinedCriterionBindersOrderRuleGroundable(Rule* rule):CombinedCriterion(rule){}
	CombinedCriterionBindersOrderRuleGroundable(Rule* rule,Priority p):CombinedCriterion(rule,p){}
	virtual ~CombinedCriterionBindersOrderRuleGroundable(){}
	virtual double assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition);
};

class CombinedCriterionAdvanced: public CombinedCriterion {
public:
	CombinedCriterionAdvanced(Rule* rule):CombinedCriterion(rule){}
	CombinedCriterionAdvanced(Rule* rule,Priority p):CombinedCriterion(rule,p){}
	virtual ~CombinedCriterionAdvanced(){}
	virtual double assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition);
};

/**
 * Return the instance of OrderRuleGroundable based on the Option parameter
 */

class OrderRuleGroundableFactory{
public:
	static OrderRuleGroundable* getInstance(Rule *rule){
		switch (Options::globalOptions()->getPositiveOrderingProcedure()) {
			case NO_ORDERING:
				return	nullptr;
				break;
			case INDEXING_ORDERING:
				return new SemiJoinIndexingArgumentsOrderRuleGroundable(rule);
				break;
			case DLV_INDEXING_ORDERING:
				return new CombinedCriterionIndexingArgumentsOrderRuleGroundable(rule);
				break;
			case DLV_BINDER_ORDERING:
				return new CombinedCriterionBindersOrderRuleGroundable(rule);
				break;
			case DLV_BINDER_INDEXING_BOUND_ATOMS_ORDERING:
				return new CombinedCriterionAdvanced(rule);
				break;
			case BINDER_ORDERING:
				return new BindersOrderRuleGroundable(rule);
				break;
			default:
				return new CombinedCriterion(rule);
				break;
		}
	}
};

}}

#endif /* SRC_GROUNDER_STATEMENT_ORDERRULEGROUNDABLE_H_ */
