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
 * File:   Names.h
 * Author: cesco
 *
 * Created on 19 aprile 2014, 16.06
 */

#ifndef NAMES_H
#define	NAMES_H

#include <string>
#include <vector>

using namespace std;

class Names {
public:
    static unsigned addPredicateName( string );
    static string getPredicateName( unsigned );
    static unsigned addStringConstant( string );
    static string getStringConstant( unsigned );
    static unsigned addIntegerConstant( int );
    static int getIntegerConstant( unsigned );
    
private:
    Names() { }
    
    static vector<string> predicateNames;
    static vector<string> stringConstants;
    static vector<int> integerConstants;
};

#endif	/* NAMES_H */

