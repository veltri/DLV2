/*
 * InteractiveStats.h
 *
 *  Created on: Mar 12, 2016
 *      Author: david
 */

#ifndef SRC_UTIL_INTERACTIVESTATS_H_
#define SRC_UTIL_INTERACTIVESTATS_H_

#include<string>
#include <vector>
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
string getTextSpace(string text,unsigned col){
	  unsigned plus=0;
	  for(char c:text)if(c=='%'){plus++;break;}
	  string spacePre="";
	  while(spacePre.size()<col)spacePre+=" ";
	  string spacePost="";
	  while(spacePre.size()+text.size()+spacePost.size()-plus<(unsigned)COLS)spacePost+=" ";
	  return spacePre+text+spacePost;
}


unsigned findCol(const vector<TableInfo>& table, TableInfo& t) {
	unsigned col = 0;
	if (t.father != 0) {
		unsigned root = t.father;
		while (root != 0) {
			col++;
			root = table[root - 1].father;
		}
	}
	return col;
}

bool haveChild(const vector<TableInfo>& table, unsigned i) {
	for(auto&t :table){
		if(t.father==i)
			return true;
	}
	return false;
}

void retractChild (vector<TableInfo>& table,unsigned father){

	for(unsigned i=0;i<table.size();i++){
		if(table[i].father==father){
			table[i].show=false;
			retractChild (table,i+1);
		}
	}

}

void expandRetractCursor (vector<TableInfo>& table,unsigned cursor){
	int display=-1;
	unsigned expand=0;
	for(unsigned i=0;i<table.size();i++){
		auto& t=table[i];
		if(t.show)
			display++;
		if(display==(int)cursor){
			expand=i+1;
			break;
		}
	}
	if(expand==0)return;
	for(unsigned i=0;i<table.size();i++){
		if(table[i].father==expand){
			table[i].show=!table[i].show;
			if(!table[i].show)
				retractChild(table,i+1);
		}

	}
//	if(!show)
//		expandRetractChild(table,expand);

}

class InteractiveStats {
public:
	InteractiveStats(){};
	static void displayStats(vector<TableInfo>&table){};
};



#else
class InteractiveStats {
public:
	InteractiveStats(){};
	static void displayStats(vector<TableInfo>&table){};
};
#endif


} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_UTIL_INTERACTIVESTATS_H_ */
