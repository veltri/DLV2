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
#include "NonGroundSimplifier.h"
#include "../output/NumericOutputBuilder.h"
#include "../exception/ConstrainException.h"


using namespace std;

namespace DLV2{

namespace grounder{

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
		predicateTable(PredicateTable::getInstance()), predicateExtTable(PredicateExtTable::getInstance()),
		statementDependency(StatementDependency::getInstance()), termsMap(TermTable::getInstance()),outputBuilder(OutputBuilder::getInstance()){
	};

	/// This method executes the overall grounding process
	virtual void ground();

	/// This method executes the grounding of a rule
	/// @param r The rule to be grounded
	/// @parm isRecursive If the rule is recursive
	/// @param firstIteraction If it is the first iteration or not (useful for recursive rules)
	bool groundRule(Rule* r);

	///Printer method
	void print() {	statementDependency->print();};

	/// Printer method for facts
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
	///Output builder
	OutputBuilder *outputBuilder;

//	///The set of grounder rules
//	GroundedRules groundedRule;
//	/// Manage the output and simplification
//	ProgramEvaluator evaluator;

	/// For each predicate in the current rule this vector stores the table of insert for the atom in head and
	/// searching table for the predicate in the body
	vector<vector<unsigned>> predicate_searchInsert_table;
	///The NonGroundSimplifier object
	NonGroundSimplifier nonGroundSimplificator;

	void swapInDelta(Rule* r);

	/* Initialize the vector of predicate_searchInsert_table with:
	 * 		Atom in head: if is recursive predicate DELTA table else NOFACT table
	 * 		Atom in body: FACT and NOFACT table
	 * 		Returns true if there is at least one atom in the body with all tables to search empty.
	 * 		In this case the rule has not to be grounded.
	*/
	bool inizializeSearchInsertPredicate(Rule* rule,unordered_set<index_object>& componentPredicateInHead);
	bool inizializeSearchInsertPredicate(Rule* rule);
	/// Based on the sequence of searching table set the table to search and insert for grounding process
	bool nextSearchInsertPredicate(Rule* rule,unordered_set<index_object>& componentPredicateInHead,unsigned token,const vector<unsigned>& originalOrderBody);


	/// Initialization of grounding rule r
	virtual void inizialize(Rule* rule) = 0;
	/// Return true if exist a match with the current atom and current assignment
	virtual bool match() = 0;
	/// Next atom in the rule, if is last return false else true
	virtual bool next() = 0;
	/// Found an assignment for the rule, return true if is grounded new knowledge
	virtual bool foundAssignment() = 0;
	/// Previous atom in the rule, if not exist return false
	virtual bool back() = 0;

	/// A vector of ground rules containing in their bodies atoms that can potentially be undef atoms.
	vector<Rule*> rulesWithPossibleUndefAtoms;
	/// For each rule in rulesWithPossibleUndefAtoms, this vector store a vector
	/// containing the positions of the atoms in that rule that can potentially be undef atoms.
	vector<vector<unsigned>> atomsPossibleUndefPositions;

	///This method iterates the rulesWithPossibleUndefAtoms, in order to see whether the atoms possible undef have been
	///derived or not:
	/// 	-If it was derived, then its index is set to the index of the derived atom
	/// 	-If it was derived as true, then (since is negative) the atom is false so the rule can be simplified
	///		-If it was not derived, then (since is false) the atom is true, so it can be simplified
	void substituteIndicesInRulesWithPossibleUndefAtoms();

private:
	///Print the program rule
	void printProgram(const vector<vector<Rule*> >& exitRules,const vector<vector<Rule*> >& recursiveRules);
	bool inizializeSearchInsertPredicateBody(Rule* rule);
	void findRecursivePredicatesInComponentRules(const unordered_set<index_object>& componentPredicateInHead, vector<unsigned>& recursivePredicatesPositions, Rule* rule, vector<unsigned >& orderedBody);
};

};

};

#endif /* PROGRAMGROUNDER_H_ */
