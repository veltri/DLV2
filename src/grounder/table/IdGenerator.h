/*
 * IdGenerator.h
 *
 *  Created on: Feb 18, 2015
 *      Author: davide
 */

#ifndef SRC_GROUNDER_TABLE_IDGENERATOR_H_
#define SRC_GROUNDER_TABLE_IDGENERATOR_H_

namespace DLV2 {
namespace grounder {

class IdGenerator {
public:
	virtual ~IdGenerator(){};

	unsigned getId(){return current_id++;};

	IdGenerator* getInstance(){
		if(idGenerator==nullptr)
			idGenerator=new IdGenerator;

		return idGenerator;
	}

	static void freeInstance(){if(idGenerator!=nullptr)delete idGenerator;};

private:
	IdGenerator():current_id(1){};
	unsigned current_id;

	static IdGenerator *idGenerator;
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_TABLE_IDGENERATOR_H_ */
