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
	for(unsigned index=0;index<ruleStats.size();index++){

		auto& rs=ruleStats[index].back();
		double recTime=0;
		unsigned groundRule=0;
		for(auto& rs:ruleStats[index]){
			recTime+=rs.time;
			groundRule+=rs.groundedRule;
		}
		unsigned time=recTime/getTotalTime()*100;
 		string ss=appendSpace(to_string(time)+"%%",8)+appendSpace(ruleStats[index][0].rule,RULESPACE)+appendSpace(to_string(recTime),TIMESPACE)+appendSpace(to_string(groundRule),GROUNDSPACE)+to_string(ruleStats[index].size());

		vec.emplace_back(ss,true,0);
		unsigned fatherRule=vec.size();
		if(rs.rule.size()>=RULESPACE){
			for (unsigned i = 0; i < rs.rule.size(); i += RULESPACE*2)
				vec.emplace_back(rs.rule.substr(i, RULESPACE*2),false,fatherRule);
		}
		for(unsigned i=0;i<rs.bodyPES.size();i++){
			if(rs.bodyPES[i].first.size()==0)continue;
			double size=rs.bodyPES[i].second;
			string ss=appendSpace(rs.bodyPES[i].first,ATOMSPACE)+"P.E.S. = "+to_string(rs.bodyPES[i].second);
			vec.emplace_back(ss,false,fatherRule);
			unsigned fatherAtom=vec.size();
			for(auto& sel:rs.varSelectivity[i]){
				unsigned select=sel.second/size*100;
				string ss=sel.first+"  Selectivity = "+to_string(select)+"%%";
				vec.emplace_back(ss,false,fatherAtom);
			}
		}

	}
	return vec;
}

RuleStatistics* RuleStatistics::getInstance() {
	if(rstats==nullptr)
		rstats=new RuleStatistics();
	return rstats;
}

void RuleStatistics::rawPrint(ostream& ss){
	string heading1="Total time: "+to_string(getTotalTime());
	string heading2="Time%   "+appendSpace("Rule",RULESPACE)+appendSpace("Time(s)",TIMESPACE)+appendSpace("N.GroundRule ",GROUNDSPACE)+"Iteration";
	ss<<heading1<<endl;
	ss<<heading2<<endl;
	for(unsigned i=0;i<ruleStats.size();i++)
		ss<<rawRuleStat(i);
}

string RuleStatistics::rawRuleStat(unsigned index){
	string ss="";
	auto& rs=ruleStats[index].back();
	double recTime=0;
	unsigned groundRule=0;
	for(auto& rs:ruleStats[index]){
		recTime+=rs.time;
		groundRule+=rs.groundedRule;
	}
	unsigned time=recTime/getTotalTime()*100;
	ss=appendSpace(to_string(time)+"%",8)+appendSpace(ruleStats[index][0].rule,RULESPACE)+appendSpace(to_string(recTime),TIMESPACE)+appendSpace(to_string(groundRule),GROUNDSPACE)+to_string(ruleStats[index].size())+'\n';
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
	if(ruleStats.size()<=index){
		ruleStats.resize(index+1);
	}

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
