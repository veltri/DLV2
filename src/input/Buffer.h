/*
 *
 *  Copyright 2014 Mario Alviano, Carmine Dodaro, Francesco Ricca and
 *                 Pierfrancesco Veltri.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

/*
 * Buffer.h
 *
 *  Created on: 20/apr/2014
 *      Author: ricca
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include<vector>
#include<ostream>
#include<cstring>

using namespace std;

namespace DLV2
{

    class Buffer {
            friend ostream& operator<<(Buffer&, ostream&);

    public:
            Buffer();
            void addBlock(char*, int);
            void lastBlock();
            void writeBlock(unsigned i, ostream&);
            void flushOn(ostream& o);

            virtual ~Buffer();

    private:

            unsigned lastBlockSize;
            Buffer(const Buffer&){ exit(122); };
            vector<char*> blocks;

    };

};

#endif /* BUFFER_H_ */
