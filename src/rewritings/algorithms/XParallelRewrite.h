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
 * File:   XParallelRewrite.h
 * Author: pierfrancesco
 *
 * Created on 26 giugno 2015, 18.27
 */

#ifndef XPARALLELREWRITE_H
#define XPARALLELREWRITE_H

#include "XRewrite.h"

#include <mutex>
#include <thread>

namespace DLV2{ namespace REWRITERS{

    class XRulesetIterator;
    class XQuery;

    class XParallelRewrite: public XRewrite {
    public:
        XParallelRewrite( XProgram& input ):
                XRewrite(input),
                queryPredIdx(0),
                nCores(std::thread::hardware_concurrency()),
                activeThreads(1) { }
        virtual ~XParallelRewrite() { }

        virtual std::vector< XRule* > rewrite();


    private:
        typedef std::list< std::vector< XRule* > > RESULT_SETS;

        void mainProcedure(
                std::vector< XQuery* >* queries,
                XRulesetIterator* rulesetIterator,
                std::vector< XRule* >& output,
                XParallelRewrite* This );
        void rewriteQuery(
                const XQuery& query,
                XRulesetIterator* rulesetIterator,
                std::vector< XQuery* >& workingQueue );
        void manageConjunctiveQuery(
                const XQuery& query,
                XRulesetIterator* rulesetIterator,
                std::vector< XQuery* >& workingQueue,
                std::vector< XRule* >& output,
                XParallelRewrite* This );
        // Reminder: the last query in vector 'splitQuery' is the merging query, thus it is not to be rewritten;
        bool existentialJoinDecomposition(
                const XQuery& query,
                std::vector< XQuery* >& splitQuery );
        void checkExistentialJoins(
                const XRule& query,
                unsigned currentLiteralPos,
                XRandomAccessSet< unsigned >& subQueryAtomPositions,
                XRandomAccessSet< index_t >& sharedNulls ) const;
        XRule* generateSubQuery(
                const XRule& query,
                const XRandomAccessSet< unsigned >& subQueryAtomPositions,
                std::vector< XLiteral >& mergeQueryBodyLiterals );
        void pushQuery( XRule* rewriting, std::vector< XQuery* >& workingQueue );
        std::vector< XQuery* >* unfold(
                const RESULT_SETS& resultSets,
                const std::unordered_map< index_t, RESULT_SETS::const_iterator >& predIdx2ResultSet,
                const std::vector< index_t >& queryPredIndices );
        XRule* unfoldingStep( const XRule& queryToBeUnfolded, unsigned literalPos, const XRule& rule );

        virtual void lockIO() { mutexIO.lock(); }
        virtual void unlockIO() { mutexIO.unlock(); }
        virtual void lockQueryPredIdx() { mutexQueryPredIdx.lock(); }
        virtual void unlockQueryPredIdx() { mutexQueryPredIdx.unlock(); }
        virtual void lockProgramVariableCounter() { mutexProgramVariableCounter.lock(); }
        virtual void unlockProgramVariableCounter() { mutexProgramVariableCounter.unlock(); }
        virtual void lockCanonicalRuleHashCodesCache() { mutexCanonicalRuleHashCodesCache.lock(); }
        virtual void unlockCanonicalRuleHashCodesCache() { mutexCanonicalRuleHashCodesCache.unlock(); }
        virtual void lockReachabilityCache() { mutexReachabilityCache.lock(); }
        virtual void unlockReachabilityCache() { mutexReachabilityCache.unlock(); }
        virtual void lockHomomorphismCache() { mutexHomomorphismCache.lock(); }
        virtual void unlockHomomorphismCache() { mutexHomomorphismCache.unlock(); }
        virtual void lockUnifierAggregationDuration() { mutexUnifierAggregationDuration.lock(); }
        virtual void unlockUnifierAggregationDuration() { mutexUnifierAggregationDuration.unlock(); }
        virtual void lockQueryNecessaryDuration() { mutexQueryNecessaryDuration.lock(); }
        virtual void unlockQueryNecessaryDuration() { mutexQueryNecessaryDuration.unlock(); }
        virtual void lockQueryEliminationDuration() { mutexQueryEliminationDuration.lock(); }
        virtual void unlockQueryEliminationDuration() { mutexQueryEliminationDuration.unlock(); }
        virtual void lockReachabilityDuration() { mutexReachabilityDuration.lock(); }
        virtual void unlockReachabilityDuration() { mutexReachabilityDuration.unlock(); }
        virtual void lockHomomorphismDuration() { mutexHomomorphismDuration.lock(); }
        virtual void unlockHomomorphismDuration() { mutexHomomorphismDuration.unlock(); }
        virtual void lockOutputRewriting() { mutexOutputRewriting.lock(); }
        virtual void unlockOutputRewriting() { mutexOutputRewriting.unlock(); }
        virtual void lockActiveThreads() { mutexActiveThreads.lock(); }
        virtual void unlockActiveThreads() { mutexActiveThreads.unlock(); }

        std::mutex mutexIO;
        std::mutex mutexQueryPredIdx;
        std::mutex mutexProgramVariableCounter;
        std::mutex mutexCanonicalRuleHashCodesCache;
        std::mutex mutexReachabilityCache;
        std::mutex mutexHomomorphismCache;
        std::mutex mutexUnifierAggregationDuration;
        std::mutex mutexQueryNecessaryDuration;
        std::mutex mutexQueryEliminationDuration;
        std::mutex mutexReachabilityDuration;
        std::mutex mutexHomomorphismDuration;
        std::mutex mutexOutputRewriting;
        std::mutex mutexActiveThreads;

        unsigned queryPredIdx;
        unsigned nCores;
        unsigned activeThreads;

    };

};};

#endif /* XPARALLELREWRITE_H */
