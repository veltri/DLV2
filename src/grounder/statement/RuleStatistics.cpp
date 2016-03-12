/*
 * RuleStatistics.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: david
 */

#include "RuleStatistics.h"
#include "../table/PredicateExtension.h"

namespace DLV2 {
namespace grounder {

string appendSpace(string text,unsigned space){
	  if(text.size()>space){
		  text.resize(space-1);
		  return text+" ";
	  }
	  string spacePost="";
	  while(text.size()+spacePost.size()<space)spacePost+=" ";
	  return text+spacePost;
}

RuleStatistics* RuleStatistics::rstats=nullptr;

vector<TableInfo> RuleStatistics::generateVecTableInfo() {
	vector<TableInfo> vec;
	return vec;
}

RuleStatistics* RuleStatistics::getInstance() {
	if(rstats==nullptr)
		rstats=new RuleStatistics();
	return rstats;
}

void RuleStatistics::rawPrint(ostream& ss){
	string heading1="Total time: "+to_string(getTotalTime());
	string heading2="Time%  "+appendSpace("Rule",RULESPACE)+appendSpace("Time(s)",TIMESPACE)+"N.GroundRule ";
	ss<<heading1<<endl;
	ss<<heading2<<endl;
	for(auto&v :ruleStats)
		ss<<rawRuleStat(v[0]);
}

string RuleStatistics::rawRuleStat(RuleStat& rs){
	string ss="";
	unsigned time=rs.time/getTotalTime()*100;
	ss=to_string(time)+"%    "+appendSpace(rs.rule,RULESPACE)+appendSpace(to_string(rs.time),TIMESPACE)+to_string(rs.groundedRule)+'\n';
	for(unsigned i=0;i<rs.bodyPES.size();i++){
		if(rs.bodyPES[i].first.size()==0)continue;
		double size=rs.bodyPES[i].second;
		ss+=appendSpace(rs.bodyPES[i].first,ATOMSPACE)+"P.E.S. = "+to_string(rs.bodyPES[i].second)+'\n';
		for(auto& sel:rs.varSelectivity[i]){
			unsigned select=sel.second/size*100;
			ss+=sel.first+"  Selectivity = "+to_string(select)+"%"+'\n';
		}
	}
	return ss;
}



void RuleStatistics::prepareStats(Rule* rule){
	unsigned index=rule->getIndex();
	if(ruleStats.size()>=index)
		ruleStats.resize(index+1);

	vector<pair<string,unsigned>> bodyPES;
	vector<vector<pair<string,unsigned>>> varSelectivity;
	bodyPES.resize(rule->getSizeBody());
	varSelectivity.resize(rule->getSizeBody());
	for(unsigned i=0;i<rule->getSizeBody();i++){
		Atom* atom=rule->getAtomInBody(i);
		if(!atom->isClassicalLiteral() || atom->isNegative())continue;
		stringstream ss;
		atom->print(ss);
		unsigned size=PredicateExtTable::getInstance()->getPredicateExt(atom->getPredicate())->getPredicateExtentionSize();
		bodyPES[i]={ss.str(),size};
		vector<pair<string,unsigned>> select;
		for(unsigned j=0;j<atom->getTermsSize();j++){
			Term* t=atom->getTerm(j);
			if(t->getType()==VARIABLE){
				PredicateInformation* pi=PredicateExtTable::getInstance()->getPredicateExt(atom->getPredicate())->getPredicateInformation();
				if(pi!=nullptr){
					unsigned selectivity=pi->getSelectivity(j);
					stringstream ss1;
					t->print(ss1);
					select.push_back({ss1.str(),selectivity});
				}
			}
		}
		if(select.size()>0)
			varSelectivity[i]=select;
	}
	stringstream ss;
	rule->print(ss);
	string str=ss.str();
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	ruleStats[index].emplace_back(str,0,bodyPES,varSelectivity);

}



} /* namespace grounder */
} /* namespace DLV2 */
