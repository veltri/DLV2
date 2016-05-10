/*
 * ArithTerm.cpp
 *
 *  Created on: 09/mar/2014
 *      Author: Davide
 */

#include "ArithTerm.h"
#include "../term/ConstantTerm.h"

#include "../hash/HashString.h"
#include "../hash/HashVecInt.h"
#include <stack>
#include "../../util/VecStack.h"

namespace DLV2{

namespace grounder{

Term* ArithTerm::calculate(vector<Term*>& terms) {
	VecStack<int> s;
	s.reserve(operators.size());
	for(auto op:operators){
		if(!op.second){
			if(terms[op.first]->getType()!=NUMERIC_CONSTANT)cerr<<"WARNING: Arithmetic term with non numeric constant "<<endl;
			int constant=terms[op.first]->getConstantValue();
			s.push(constant);
		}else{
			int c1=s.pop();
			int c2=s.pop();
			Operator operat=unsignedToOperator(op.first);
			int result=0;
			if (operat == Operator::PLUS)
				result = c2+c1;
			else if (operat == Operator::MINUS)
				result =c2-c1;
			else if (operat == Operator::DIV){
				//FIXME For not stop the program division by 0 is 0
				if(c1 != 0)
					result = c2/c1;
				else
					result = 0;
			}else if (operat == Operator::TIMES)
				result = c2*c1;
			s.push(result);
		}
	}
	int result = s.pop();
	Term *constantTerm=new NumericConstantTerm(result<0,result);
	return constantTerm;

}


LINE ArithTerm::transformToLineEq(){
	stack<LINE> s;
	for(auto op:operators){
		if(!op.second){
			s.push(terms[op.first]->transformToLineEq());
		}else{
			LINE c1=s.top();
			s.pop();
			LINE c2=s.top();
			s.pop();
			Operator operat=unsignedToOperator(op.first);
			LINE result;
			if (operat == Operator::PLUS)
				result = c2+c1;
			else if (operat == Operator::MINUS)
				result =c2-c1;
			else if (operat == Operator::DIV){
				//FIXME For not stop the program division by 0 is 0
				result = c2/c1;
			}else if (operat == Operator::TIMES)
				result = c2*c1;
			s.push(result);
		}
	}
	return s.top();
}

size_t ArithTerm::hash() {
	vector<size_t> hashVec(terms.size()+(operators.size()*2));
	hashVec[0]=terms[0]->getIndex();
	for(auto o:operators){
		if(!o.second)
			hashVec.push_back(terms[o.first]->getIndex());
		else
			hashVec.push_back(o.first);
	}
	return HashVecInt::getHashVecInt()->computeHashSize_T(hashVec);
}

void ArithTerm::print(ostream& stream) {
	stack<string> expression;
	for(auto op:operators){
		if(!op.second){
			stringstream ss;
			terms[op.first]->print(ss);
			expression.push(ss.str());
		}else{
			string s1=expression.top();
			expression.pop();
			string s2=expression.top();
			expression.pop();
			Operator operat=unsignedToOperator(op.first);
			expression.push("("+s2+getNameOperator(operat)+s1+")");
		}
	}

	stream<<expression.top();
}

string ArithTerm::getNameOperator(Operator op) {
	if (op == Operator::PLUS)
		return "+";
	if (op == Operator::MINUS)
		return "-";
	if (op == Operator::TIMES)
		return "*";
	if (op == Operator::DIV)
		return "/";
	return "";
}

Operator ArithTerm::getOperatorName(char op) {
	if (op == '+')
		return Operator::PLUS;
	if (op == '-')
		return Operator::MINUS;
	if (op == '*')
		return Operator::TIMES;
	if (op == '/')
		return Operator::DIV;
	return Operator::DIV;
}

 bool ArithTerm::operator==(const Term& term)const{
	if(getType()!=term.getType())return false;
	if(operators.size()!=term.getSizeOperator())return false;
	if(terms.size()!=term.getTermsSize())return false;
	for(unsigned int i=0;i<operators.size();i++)
		if(operators[i].first!=term.getOperator(i).first || operators[i].second!=term.getOperator(i).second)
			return false;
	for(unsigned int i=0;i<terms.size();i++)
		if(terms[i]->getIndex()!=term.getTerm(i)->getIndex())
			return false;

	return true;
}

Term* ArithTerm::substitute(var_assignment& substritutionTerm) {
	// Create a new arithmetic term replacing the term in a vector
	// Recursively call substitute for nested function
	// At the end add a new term in a table and return index

	TermTable *termTable=TermTable::getInstance();
	vector<Term*> subTerms(terms.size());
	for(unsigned int i=0;i<terms.size();i++){
		Term* sub_term=terms[i]->substitute(substritutionTerm);
		subTerms[i]=sub_term;
	}

	Term *newTerm=new ArithTerm(negative,operators,subTerms);
	termTable->addTerm(newTerm);
	return  newTerm;
}

int ArithTerm::substituteAndCalculate(var_assignment& substritutionTerm){
	//Substitute the variable in the Arith term and calculate the value
	//The term returned is not added in the table Term

	vector<Term*> subTerms(terms.size());
	for(unsigned int i=0;i<terms.size();i++){
		subTerms[i]=terms[i]->substitute(substritutionTerm);
	}

	int result = calculate(subTerms)->getConstantValue();
	return result;
}

void ArithTerm::addArithTerm(Term* arith,Term* term,Operator op){
	if(term->getType()!=ARITH){
		arith->addTerm(term);
		arith->addOperator(op);
		return;
	}
	for(unsigned i=0;i<term->getSizeOperator();i++){
		auto oop=term->getOperator(i);
		if(!oop.second)
			arith->addTerm(term->getTerm(oop.first));
		else
			arith->addOperator(unsignedToOperator(oop.first));
	}
	arith->addOperator(op);

}

Operator ArithTerm::unsignedToOperator(unsigned op){
	switch (op) {
		case 0:
			return PLUS;
			break;
		case 1:
			return MINUS;
			break;
		case 2:
			return DIV;
			break;
		case 3:
			return TIMES;
			break;
		default:
			return PLUS;
			break;
	}
}

};

};
