/*
 * InteractiveStats.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: david
 */

#include "InteractiveStats.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

namespace DLV2 {
namespace grounder {

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
void InteractiveStats::displayStats(vector<TableInfo>&table,string heading1,string heading2){

//	initscr();
    SCREEN* s = NULL;
	FILE* out = stdout;
	if(!isatty(fileno(stdout))) {
		out = fopen("/dev/tty", "w");
		// Should really test `out` to make sure that worked.
		setbuf(out, NULL);
	}
	s = newterm(NULL, out, stdin);

	start_color();
	curs_set(0);
	noecho();
	keypad(stdscr, TRUE);
	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_BLACK,COLOR_WHITE);
	init_pair(3,COLOR_WHITE,COLOR_BLUE);

	unsigned cursor=0;
	bool finish=false;
	int key=0;
	while(!finish){

		unsigned lineDisplay=0;
		attron(COLOR_PAIR(3));
		mvprintw(0,0,getTextSpace(heading1,0).c_str());
		mvprintw(1,0,getTextSpace(heading2,0).c_str());
		unsigned line=2;
		for(unsigned i=0;i<table.size();i++){
			TableInfo& t=table[i];
			if(!t.show)continue;
			if(line-2==cursor)
				attron(COLOR_PAIR(2));
			else
				attron(COLOR_PAIR(1));

			unsigned col = findCol(table, t);
			string child=(haveChild(table,i+1))?"+  ":"   ";

			mvprintw(line,0,getTextSpace(child+t.label,col).c_str());
			line++;
			lineDisplay++;
		}

		string info=to_string(cursor)+" "+to_string(key);
		mvprintw(LINES-1,0,info.c_str());
		key=getch();
		switch (key) {
			case KEY_UP:
				if(cursor>0)
					cursor--;
				break;
			case KEY_DOWN:
				if(cursor<lineDisplay-1)
					cursor++;
				break;
			case 'q':
				finish=true;
				break;
			case 10:
				expandRetractCursor(table,cursor);
				break;
			default:
				break;
		}
		clear();

		//timeout(500);
		refresh();
	}
	endwin();
    delscreen(s);

}

#endif

} /* namespace grounder */
} /* namespace DLV2 */
