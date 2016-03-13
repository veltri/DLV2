/*
 * InteractiveStats.h
 *
 *  Created on: Mar 12, 2016
 *      Author: david
 */

#ifndef SRC_UTIL_INTERACTIVESTATS_H_
#define SRC_UTIL_INTERACTIVESTATS_H_

#include <string>
#include <vector>
#include <iostream>
#ifdef NCURSES
#include <ncurses.h>
#endif

using namespace std;

namespace DLV2 {
namespace grounder {

struct TableInfo{

	TableInfo(string label,bool show,	unsigned father):label(label),show(show),father(father){};

	string label;
	bool show;
	unsigned father;
};




#ifdef NCURSES


class InteractiveStats {
public:
	InteractiveStats(){};
	static void displayStats(vector<TableInfo>&table,string heading1,string heading2);
};



#else
class InteractiveStats {
public:
	InteractiveStats(){};
	static void displayStats(vector<TableInfo>&table){cerr<<"ERROR: NCURSES NOT SUPPORTED"<<endl;};
};
#endif


} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_UTIL_INTERACTIVESTATS_H_ */
