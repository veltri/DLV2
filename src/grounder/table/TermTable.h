/*
 * TermTable.h
 *
 *  Created on: 26/feb/2014
 *      Author: Davide
 */

#ifndef TERMTABLE_H_
#define TERMTABLE_H_


#include "../term/Term.h"
#include "../term/ConstantTerm.h"
#include "../term/VariableTerm.h"
#include "../hash/Hashable.h"

using namespace std;

namespace DLV2{

namespace grounder{


/*
 *  TermTable is an abstract class that represent a table of all Term in
 *  the logical program
 *
 *  TermTable is a Singleton
 */
class TermTable {
public:
	///Add term in the table and return the index
	virtual void addTerm(Term *&t){	terms.insert(t);}
	/// Get term
	virtual void getTerm(Term*& t){	terms.get(t);}
	/// Get size of the table
	virtual unsigned int getSize(){	return terms.flyweight_set.size();}
	/// Get the number of collision of the IdManager
	//TODO
	virtual int getCollision(){return 0;};

	virtual Term* generateVariableAuxTerm(){
		string s("#aux"+to_string(counter++));
		Term * term=new VariableTerm(false,s);
		addTerm(term);
		return term;
	}

	// Method for fetch the instance of singleton
    // If termTable is null instance the table based on parameter in the configuration
	static TermTable* getInstance();
	virtual ~TermTable(){};

	//please not modify me :(
	Term* term_max;
	Term* term_min;
	Term* term_zero;
protected:
	// Instance of the singleton
	static TermTable* termTable;
private:
//	TermTable(): term_max(new StringConstantTerm(false,"+∞")), term_min(new StringConstantTerm(false,"-∞")), term_zero(new NumericConstantTerm(false,0)) {
	TermTable(): term_max(new StringConstantTerm(false,"#sup")), term_min(new StringConstantTerm(false,"#inf")), term_zero(new NumericConstantTerm(false,0)),counter(0) {
		addTerm(term_max);
		addTerm(term_min);
		addTerm(term_zero);
	}
	/*
	 *  Flyweight Factory of terms
	 */
	FlyweightIndexFactory<Term> terms;

	unsigned counter;
};


};

};

#endif /* TERMTABLE_H_ */
