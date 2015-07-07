/*
 * IdGenerator.h
 *
 *  Created on: Feb 18, 2015
 *      Author: davide
 */

#ifndef SRC_GROUNDER_TABLE_IDGENERATOR_H_
#define SRC_GROUNDER_TABLE_IDGENERATOR_H_

#include <vector>

using namespace std;

namespace DLV2 {
namespace grounder {


class IdGenerator {
public:
	virtual ~IdGenerator(){};


	unsigned getNewId(unsigned id=0){
		return ++(idGenerators[id]);
	}

	unsigned generateId(unsigned init){
		idGenerators.push_back(init);

		return idGenerators.size()-1;
	}

	static IdGenerator* getInstance(){
		if(idGenerator==nullptr)
			idGenerator=new IdGenerator;

		return idGenerator;
	}



private:
	IdGenerator():INIT_VALUE(1){idGenerators.push_back(INIT_VALUE);idGenerators.push_back(INIT_VALUE);};

	static IdGenerator *idGenerator;
	vector<unsigned> idGenerators;
	unsigned INIT_VALUE;
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_TABLE_IDGENERATOR_H_ */
