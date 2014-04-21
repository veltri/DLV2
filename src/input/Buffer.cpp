/*
 * Buffer.cpp
 *
 *  Created on: 20/apr/2014
 *      Author: ricca
 */

#include "Buffer.h"
#include <iostream>

Buffer::Buffer() : blocks(20), lastBlockSize(0){
	for (unsigned i = 0; i < 20; ++i)
		blocks[i] = 0;
}

void Buffer::addBlock(char* b, int size) {
        lastBlockSize = size;
	char* bc = new char[size];
	memcpy(bc,b,size*sizeof(char));
	blocks.push_back(bc); 
}
void Buffer::lastBlock()
{
  if(blocks.size())
  {
    blocks.back()[lastBlockSize] = '\0';
    blocks.back()[--lastBlockSize] = '\0';
  }
}


void Buffer::writeBlock(unsigned i, ostream& o)
{
	if(blocks[i])
	{
		o << blocks[i];
		delete [] blocks[i];
		blocks[i] = 0;
	}
}

Buffer::~Buffer() {
	for(unsigned i = 0; i < blocks.size(); ++i)
		if(i)
			delete [] blocks[i];
}


ostream& operator<<(Buffer& b, ostream& o)
{
	for(unsigned i = 0; i < b.blocks.size(); ++i)
		b.writeBlock(i,o);
	return o;
}

void Buffer::flushOn(ostream& o) {
/*if(blocks.size())
{
char* last = blocks.back();
int g=0;
int lastdot= 0;
while(last[g]!='\0')
{
if(last[g] == '.') lastdot=g;
 cerr << g << last[g] << endl; g++;
};

last[lastdot+1]='\0';

}
*/
	for(unsigned i = 0; i < blocks.size(); ++i)
		writeBlock(i,o);
}











