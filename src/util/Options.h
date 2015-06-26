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
 * File:   Options.h
 * Author: cesco
 *
 * Created on 4 aprile 2014, 12.52
 */

#ifndef OPTIONS_H
#define	OPTIONS_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Constants.h"

namespace DLV2
{


    class Options{
    public:

        void init( int argc, char* const* argv );

        static Options* globalOptions();
        
        static void finalizeGlobalOptions();

        bool isAspCore2Strict() const { return aspCore2Strict; }

        const std::vector<const char*>& getInputFiles() const { return inputFiles; }
        
        bool getPrintProgram() const { return printProgram; }
        
        bool getPrintDepGraph() const { return printDepGraph; }
        
        bool getPrintStatistics() const { return printStatistics; }

        INPUT_BUILDER_POLICY getInputBuilderPolicy() const { return inputPolicy; }

        OUTPUT_POLICY getOutputPolicy() const { return outputPolicy; }

        unsigned getNamedpipe() const { return namedpipe; }
        
        const std::string& getDBDataSource() const { return dbDataSource; }
        
        const std::string& getDBUsername() const { return dbUsername; }
        
        const std::string& getDBPassword() const { return dbPassword; }

        unsigned getIndexType() const {return this->indexType;}

    	void setIndexType(unsigned indexType) {this->indexType=indexType;}

    	unsigned getHashType() const {return this->hashType;}

    	void setHashType(unsigned hashType) {this->hashType = hashType;}

    	const std::string& getPredicatesIndexTerm() const {return predicatesIndexTerm;}

		void setPredicateIndexTerm(const std::string& predIndexTerm) {this->predicatesIndexTerm = predIndexTerm; this->splitOption(predicatesIndexTerm, predicatesIndexTermMap);}

    	const std::string& getPredicatesIndexType() const {return predicatesIndexType;}

		void setPredicateIndexType(const std::string& predIndexType) {this->predicatesIndexType = predIndexType; this->splitOption(predicatesIndexType, predicatesIndexTypeMap);}

    	int getPredicateIndexTerm(const std::string& predicate);

    	int getPredicateIndexType(const std::string& predicate);

        bool isNofacts() const {return nofacts;}

		bool isPrintRewrittenProgram() const {return printRewrittenProgram;}

		unsigned getRewritingType() const {	return rewritingType;}

        ~Options() { /*if (instance != NULL) delete instance;*/ }

    private:

        static Options* instance;

        Options();

        Options(const Options& o);

        void setOutputPolicy(OUTPUT_POLICY outPolicy) { outputPolicy = outPolicy; }

        void setInputBuilderPolicy(INPUT_BUILDER_POLICY inPolicy) { inputPolicy = inPolicy; }

        void setInputFiles(const std::vector<const char*>& inFiles) { inputFiles = inFiles; }

        void setAspCore2Strict(bool strict) { aspCore2Strict = strict;	}

    	void splitOption(const std::string& string, std::unordered_map<std::string, unsigned int>& map);

        std::vector< const char* > inputFiles;

        bool aspCore2Strict;
        
        bool printProgram;
        
        bool printDepGraph;
        
        bool printStatistics;
        
        INPUT_BUILDER_POLICY inputPolicy;
        
        OUTPUT_POLICY outputPolicy;
        
        unsigned namedpipe;
        
        std::string dbDataSource;

        std::string dbUsername;
        
        std::string dbPassword;

        unsigned hashType;

        unsigned indexType;

    	std::string predicatesIndexTerm;

    	std::string predicatesIndexType;

    	///The map containing the mapping between a predicate and the position of its indexing term
    	std::unordered_map<std::string, unsigned int> predicatesIndexTermMap;

    	///The map containing the mapping between a predicate and the kind of index to be used
    	std::unordered_map<std::string, unsigned int> predicatesIndexTypeMap;

    	bool nofacts;

    	bool printRewrittenProgram;

    	unsigned rewritingType;
    };
    
};

#endif	/* OPTIONS_H */
