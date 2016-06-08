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
 * File:   Constants.h
 * Author: cesco
 *
 * Created on 4 aprile 2014, 16.29
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <set>

namespace DLV2
{
// Input builder constants
#define BUILDER_MOCK_OBJECTS 0
#define BUILDER_DLV_DB 1
#define BUILDER_IN_MEMORY 2
#define BUILDER_SELECTOR 3
#define BUILDER_DEPGRAPH 4
#define BUILDER_EMPTY 5
    
// Output builder constants
#define OUTPUT_ASPCORE2 0
#define OUTPUT_SILENT 1
    
// Dependency graph constants
#define POSITIVE_EDGE 0
#define NEGATIVE_EDGE 1
    
// DLV2 constants
#define DLV2_STRING "DLV 2.0\n"
    
// Error messages
#define ERROR_PARSING "\nError during parsing"
#define ERROR_GENERIC "\nGeneric error"
#define ERROR_DB "\nDatabase error"
#define ERROR_PARSING_CODE 100
#define ERROR_GENERIC_CODE 110
#define ERROR_DB_CODE 120
    
// New types
typedef unsigned int INPUT_BUILDER_POLICY;
typedef unsigned int OUTPUT_POLICY;

namespace DB{
    
    // Database constants
    #define TABLE_NAMES "table_names"
    #define EXECUTION_TIMESTAMP "execution_timestamp"
    #define PREDICATE_TIMESTAMP "predicate_timestamp"
    
    // New types
    typedef size_t index_t;
    typedef std::set< unsigned > DBRuleSet;
    typedef int64_t Timestamp;
};

namespace grounder{

	#define STL_HASH 0
	#define BOOST_HASH 1
	#define JAVA_HASH 2
	#define MUR_HASH 3
	#define PERL_DJ 4
	#define PERL_B 5

	#define DEFAULT 0
	#define MAP 1
	#define MULTIMAP 2
	#define HASHSET 3
	#define DOUBLEMAP 4
	#define MAP_DICTIONARY_INTERSECTION 5
	#define MAP_VECTOR 6
	#define MAP_HISTORY_VECTOR 7
	#define SINGLE_ARG_FULL 8
	#define DEFAULT_RECURSIVE 9
	#define MAP_PAIR_HISTORY_VECTOR 10
	#define DOUBLEMAP_PAIR 11
	#define MULTIPLE_TERMS 12
	#define HISTORY_HASHSET 13


	#define NATIVE_CHOICE 0
	#define DISJUNCTION 1
	#define NATIVE_CHOICE2 2
	#define COMPACT_NATIVE_CHOICE 3

	#define OUTPUT_NUMERIC 0
	#define OUTPUT_TEXTUAL 1
	#define OUTPUT_QUERY_TEXTUAL 2

	#define BACKTRACKING 0
	#define BACKJUMPING 1

	#define ARRAY_SIZE 64
	#define ATOMS_IN_RULE 32

	#define NO_ORDERING 0
	#define DLV_ORDERING 1
	#define INDEXING_ORDERING 2
	#define DLV_INDEXING_ORDERING 3
	#define DLV_BINDER_ORDERING 4
	#define DLV_BINDER_INDEXING_BOUND_ATOMS_ORDERING 5
	#define BINDER_ORDERING 6
	#define DLV_ORDERING_FUNCTION 7
	#define DLV_ORDERING_VARS_OCCURENCIES 8
	#define DLV_ORDERING_COMPARISONS_ESTIMATION 9

	#define STATS_RAW 1
	#define STATS_INTERACTIVE 2


	#define FRONTEND_BRAVE 1
	#define FRONTEND_CAUTIOUS 2

	#define PREDNAME_QUERY "#query"


	typedef unsigned index_object;

};

};

#endif	/* CONSTANTS_H */

