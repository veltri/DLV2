/*
 * RuleStatistics.h
 *
 *  Created on: Mar 12, 2016
 *      Author: david
 */

#ifndef SRC_GROUNDER_STATEMENT_RULESTATISTICS_H_
#define SRC_GROUNDER_STATEMENT_RULESTATISTICS_H_

#include <vector>
#include <string>
#include "Rule.h"
#include "../../util/Options.h"
#include "../../util/InteractiveStats.h"

namespace DLV2 {
namespace grounder {

string appendSpace(string text,unsigned space);

class RuleStatistics {

	struct RuleStat{
		RuleStat(string rule,double time,vector<pair<string,unsigned>> bodyPES,vector<vector<pair<string,unsigned>>> varSelectivity):
			rule(rule),time(time),groundedRule(0),bodyPES(bodyPES),varSelectivity(varSelectivity){}
		string rule;
		float time;
		unsigned groundedRule;
		vector<pair<string,unsigned>> bodyPES;
		vector<vector<pair<string,unsigned>>> varSelectivity;
	};
public:

	void groundNewRule(unsigned index){
		ruleStats[index].back().groundedRule++;
	}

	void setTime(unsigned index,double time){
		ruleStats[index].back().time=time;
	}

	double getTotalTime(){
		double t=0;
		for(auto& v1:ruleStats)
			for(auto& rs:v1)
				t+=rs.time;
		return t;
	}

	void prepareStats(Rule* rule);

	vector<TableInfo> generateVecTableInfo();

	void printStats(){
		sortVectorByTime();
		unsigned print=Options::globalOptions()->getPrintGroundStats();
		if(print==STATS_RAW)
			rawPrint(cerr);
		else if(print==STATS_INTERACTIVE){
			vector<TableInfo> vec=generateVecTableInfo();
//			for(auto& ti:vec){
//				cerr<<ti.label<<" "<<ti.show<<" "<<ti.father<<endl;
//			}
			InteractiveStats::displayStats(vec,"Total time: "+to_string(getTotalTime()),"   Time%%  "+appendSpace("Rule",RULESPACE)+appendSpace("Time(s)",TIMESPACE)+appendSpace("N.GroundRule",GROUNDSPACE)+"Iteration");
		}

	}

	void rawPrint(ostream& ss=cout);

	string rawRuleStat(unsigned );

	void sortVectorByTime();

	static RuleStatistics* getInstance();

    static void freeInstance(){delete rstats;}

private:
	RuleStatistics(){};
	vector<vector<RuleStat>> ruleStats;
	static RuleStatistics* rstats;

	const unsigned RULESPACE=60;
	const unsigned TIMESPACE=20;
	const unsigned ATOMSPACE=30;
	const unsigned GROUNDSPACE=14;
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_STATEMENT_RULESTATISTICS_H_ */
