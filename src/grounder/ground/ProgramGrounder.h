/*
 * ProgramGrounder.h
 *
 *  Created on: 10/apr/2014
 *      Author: Davide
 */

#ifndef PROGRAMGROUNDER_H_
#define PROGRAMGROUNDER_H_

#include <vector>

#include "ProgramEvaluator.h"
#include "../table/PredicateTable.h"
#include "../table/PredicateExtension.h"
#include "../table/TermTable.h"
#include "StatementDependency.h"
#include "../statement/GroundRule.h"

using namespace std;

namespace DLV2{

namespace grounder{

/* Table of Predicate Extensione:
 * 		FACT: Table of fact
 * 		NOFACT: Table of atom derived
 * 		DELTA, NEXTDELTA: Ausiliary table for grounding recursive rule
*/
#define FACT 0
#define NOFACT 1
#define DELTA 2
#define NEXTDELTA 3

/**
 * @brief This class manages and executes the grounding process.
 *
 * The grounding of rule process is a template method.
 */
class ProgramGrounder {

public:
	/** Constructor
	 *	@param pt A pointer to the predicate table
	 *	@param it A pointer to the instances table
	 *	@param st A pointer to the statement dependency table
	 *	Since the term table is a singleton, it is not needed to give it as a parameter.
	 */
	ProgramGrounder() :
			predicateTable(PredicateTable::getInstance()), predicateExtTable(PredicateExtTable::getInstance()), statementDependency(StatementDependency::getInstance()), termsMap(TermTable::getInstance()){};

	///This method executes the overall grounding process
	virtual void ground();

	/// This method executes the grounding of a rule
	/// @param r The rule to be grounded
	/// @parm isRecursive If the rule is recursive
	/// @param firstIteraction If it is the first iteration or not (useful for recursive rules)
	bool groundRule(Rule* r);

	///Printer method
	void print() {	statementDependency->print();};

	//Printer method for facts
	void printFact() {	predicateExtTable->print(FACT);};

	/// Return the InstanceTable
	PredicateExtTable* getInstanceTable() {	return predicateExtTable;};

	/// Return the StatementDependency
	StatementDependency* getStatementDependency() {	return statementDependency;};

	/// Return the PredicateTable
	PredicateTable* getPredicateTable() {return predicateTable;};

	///Destructor
	virtual ~ProgramGrounder();

protected:
	///A pointer to the predicate table
	PredicateTable* predicateTable;
	///A pointer to the instances table
	PredicateExtTable* predicateExtTable;
	///A pointer to the statement table
	StatementDependency* statementDependency;
	///A pointer to the terms table
	TermTable* termsMap;
//	///The set of grounder rules
//	GroundedRules groundedRule;
//	/// Manage the output and simplification
//	ProgramEvaluator evaluator;

	/// Vector that stores the combination of searching table with the predicates of current rule
	vector<bool> predicate_combination;
	///For each predicate in the current rule this vector stores the table of insert for the atom in head and
	/// searching table for the predicate in the body
	vector<vector<unsigned>> predicate_searchInsert_table;


	void swapInDelta(Rule* r);

	/* Inizialize the vector of predicate_searchInsert_table with:
	 * 		Atom in head: if is recursive predicate DELTA table else NOFACT table
	 * 		Atom in body: FACT and NOFACT table
	*/
	void inizializeSearchInsertPredicate(Rule* rule,unordered_set<index_object>& componentPredicateInHead);
	void inizializeSearchInsertPredicate(Rule* rule);
	/// Based on the sequence of searching table set the table to search and insert for grounding process
	void nextSearchInsertPredicate(Rule* rule,unordered_set<index_object>& componentPredicateInHead);
	/// Inizialize the combination of searching table, FACT and NOFACT
	void inizializeRecursiveCombinationPredicate(Rule* rule,unordered_set<index_object>& componentPredicateInHead);
	/// Calculate the next sequence of searching table during the grounding of recursive rule
	void computeRecursiveCombinationPredicate();


	/// Inizialization of grounding rule r
	virtual void inizialize(Rule* rule) = 0;
	/// Return true if exist a match with the current atom and current assignment
	virtual bool match() = 0;
	/// Next atom in the rule, if is last return false else true
	virtual bool next() = 0;
	/// Found an assignment for the rule, return true if is grounded new knowledge
	virtual bool foundAssignment() = 0;
	/// Previous atom in the rule, if not exist return false
	virtual bool back() = 0;



};

};

};

#endif /* PROGRAMGROUNDER_H_ */
