/*
 * NumericOutputBuilder.h
 *
 *  Created on: Jul 7, 2015
 *      Author: davide
 */

#ifndef SRC_GROUNDER_OUTPUT_NUMERICOUTPUTBUILDER_H_
#define SRC_GROUNDER_OUTPUT_NUMERICOUTPUTBUILDER_H_

#include <sstream>
#include "OutputBuilder.h"
#include "../ground/StatementDependency.h"

namespace DLV2 {
namespace grounder {

class NumericOutputBuilder: public OutputBuilder {
public:

    using id_weight_label= tuple<unsigned,int,vector<Term*>>;
    using pair_level_tuple_list = pair<int,list<id_weight_label>>;
    using list_pair_it=list<pair_level_tuple_list>::iterator;

	NumericOutputBuilder():printStream(false){};
	virtual ~NumericOutputBuilder(){};

    virtual void onRule(Rule *rule);
    virtual void onWeakConstraint();
    virtual void onQuery();
    virtual void onHeadAtom(Atom * atom);
    virtual void onDisjunctionAtom(const vector<Atom*>& head);
    virtual void onConstraint(Rule* rule);
    virtual void onHead(const vector<Atom*>& head);
    virtual void onBody(Rule *rule);
    virtual void onClassicalLiteral(Atom *atom);
    virtual void onChoiceAtom(Atom *atom);
    virtual unsigned onAggregate(Atom *atom);
    virtual void onAggregateElement(Atom *atom);
    virtual void onFact(Atom* atom);
    virtual void onEnd();

    virtual unsigned printCountSumAggregate(Atom *atom);
    virtual unsigned onWeightRule(Atom *aggregateAtom,unsigned bound);
    virtual unsigned onConstraintRule(Atom *aggregateAtom,unsigned bound);

    virtual unsigned printMaxMinAggregate(Atom *atom);
    virtual void printAuxRuleMinMax(Atom *aggregate,function<unsigned(Term*)>& function,unsigned& positivePredicate,unsigned& negativePredicate);

    virtual void appendToStreamAtomTable(Atom* atom);

    ///Print weak constraint
	virtual void printWeak();

	///Write the body of the rule in a new rule with in the head new aux atom and return the id of the new aux
	virtual unsigned rewriteBodyInAux(Rule* rule);

	///Create for each id in idatoms a rule with in the head a new aux atom and in the body an element in the vector. Return
	/// the id of the new aux atom in the head.
	virtual unsigned createMultipleRule(vector<unsigned>& idatoms);

	///Print the weak in the list. All the weak on the list have the same level
	void printWeakAtLevel(list<id_weight_label>& listOfWeak);



private:
    stringstream stream;
    stringstream streamAtomTable;
    bool printStream;

    //id_weight_label represent a tuple of : body of the weak rewrited, the weight and the label of the weak
    // weakLevelConstraints is a list of list, which the second list group the weak with the same level
    list<pair_level_tuple_list> weakLevelConstraints;
    // Map for each level return the iterator of the list that group the weak with the level in the key
    unordered_map<unsigned,list_pair_it> levelWeak;
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_OUTPUT_NUMERICOUTPUTBUILDER_H_ */
