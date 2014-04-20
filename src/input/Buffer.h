/*
 * Buffer.h
 *
 *  Created on: 20/apr/2014
 *      Author: ricca
 */

#include<vector>
#include<ostream>

using namespace std;


#ifndef BUFFER_H_
#define BUFFER_H_

class Buffer {
	friend ostream& operator<<(Buffer&, ostream&);

public:
	Buffer();
	void addBlock(char*, int);
	void writeBlock(unsigned i, ostream&);
	void flushOn(ostream& o);

	virtual ~Buffer();

private:

	Buffer(const Buffer&){ exit(122); };
	vector<char*> blocks;

};

#endif /* BUFFER_H_ */
