/*
 * Term.cpp
 *
 *  Created on: Jun 18, 2015
 *      Author: jessica
 */

#include "Term.h"
#include "../table/TermTable.h"

namespace DLV2{
namespace grounder{

bool Term::isTermMax() const {return this->getIndex()==TermTable::getInstance()->term_max->getIndex();}
bool Term::isTermMin() const {return this->getIndex()==TermTable::getInstance()->term_min->getIndex();}
bool Term::isTermZero() const {return this->getIndex()==TermTable::getInstance()->term_zero->getIndex();}

}}
