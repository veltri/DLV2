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
 * File:   XParallelRewrite.cpp
 * Author: pierfrancesco
 *
 * Created on 26 giugno 2015, 18.51
 */

#include "XParallelRewrite.h"

#include "../../util/Trace.h"
#include "../../util/Options.h"
#include "../../util/Constants.h"
#include "../data/XHead.h"
#include "../data/XPieceUnifier.h"
#include "../data/XRulesetIteratorNonSub.h"
#include "../data/XRulesetIteratorStandard.h"
#include "../data/XRulesetIteratorSub.h"
#include "../data/XQuery.h"

using namespace DLV2::REWRITERS;
using namespace std;

std::vector< XRule* >
XParallelRewrite::rewrite()
{
    auto sTime = std::chrono::high_resolution_clock::now();
    assert_msg( inputProgram.getQuery() != NULL, "The input query is null." );
    trace_msg( rewriting, 1, "Start by adding the input query rules to the final rewriting: " );

    inputProgram.computePredicateNullsets();

    vector< XRule* > outputRewriting;
    addInputQueries(outputRewriting);

    vector< XQuery* >* inputQueries = new vector< XQuery* >();
    for( unsigned i=0; i<outputRewriting.size(); i++ )
        inputQueries->push_back(inputProgram.createQuery(outputRewriting[i]));

    // The following iterator will be destroyed by method "mainProcedure".
    XRulesetIterator* rulesetIterator = new XRulesetIteratorStandard(inputProgram);

    trace_msg( rewriting, 3, "This is the main thread" );

    mainProcedure(inputQueries,rulesetIterator,outputRewriting,this);

//    ThreadData threadData;
//    threadData.This = this;
//    threadData.queries = inputQueries;
//    threadData.ruleset = rulesetIterator;
//    threadData.output = &outputRewriting;
//    trace_msg( rewriting, 3, "Start the main thread" );
//    pthread_t mainThread;
//    pthread_attr_t mainThreadAttr;
//    pthread_attr_init(&mainThreadAttr);
//    pthread_attr_setdetachstate(&mainThreadAttr, PTHREAD_CREATE_JOINABLE);
//    pthread_mutex_init(&mutexIO,NULL);
//    pthread_mutex_init(&mutexQueryPredIdx,NULL);
//    pthread_mutex_init(&mutexProgramVariableCounter,NULL);
//    pthread_mutex_init(&mutexCanonicalRuleHashCodesCache,NULL);
//    pthread_mutex_init(&mutexReachabilityCache,NULL);
//    pthread_mutex_init(&mutexHomomorphismCache,NULL);
//    pthread_mutex_init(&mutexUnifierAggregationDuration,NULL);
//    pthread_mutex_init(&mutexQueryNecessaryDuration,NULL);
//    pthread_mutex_init(&mutexQueryEliminationDuration,NULL);
//    pthread_mutex_init(&mutexReachabilityDuration,NULL);
//    pthread_mutex_init(&mutexHomomorphismDuration,NULL);
//    pthread_mutex_init(&mutexOutputRewriting,NULL);
//    int rc = pthread_create(&mainThread,&mainThreadAttr,threadEntryFunction,(void*)&threadData);
//    if( rc )
//    {
//       cerr << "ERROR; return code from pthread_create() is " << rc << endl;
//       exit(-1);
//    }
//    pthread_attr_destroy(&mainThreadAttr);
//    void* returnStatus;
//    rc = pthread_join(mainThread, &returnStatus);
//    if( rc )
//    {
//        cerr << "ERROR; return code from pthread_join() is " << rc << endl;
//        exit(-1);
//    }
//    trace_msg( rewriting, 3, "Main thread: work completed!" );
//    pthread_mutex_destroy(&mutexIO);
//    pthread_mutex_destroy(&mutexQueryPredIdx);
//    pthread_mutex_destroy(&mutexProgramVariableCounter);
//    pthread_mutex_destroy(&mutexCanonicalRuleHashCodesCache);
//    pthread_mutex_destroy(&mutexReachabilityCache);
//    pthread_mutex_destroy(&mutexHomomorphismCache);
//    pthread_mutex_destroy(&mutexUnifierAggregationDuration);
//    pthread_mutex_destroy(&mutexQueryNecessaryDuration);
//    pthread_mutex_destroy(&mutexQueryEliminationDuration);
//    pthread_mutex_destroy(&mutexReachabilityDuration);
//    pthread_mutex_destroy(&mutexHomomorphismDuration);
//    pthread_mutex_destroy(&mutexOutputRewriting);
    // Before returning, erase eventual rules containing atoms "aux_X" where X is an int, because they might be
    // added by some DL2Datalog translators in order to normalize conjunctive heads.
    // Notice that, erasing elements from a vector is expensive, thus it is worth creating a new vector from scratch.
    vector< XRule* > outputRewritingWithoutAuxAtoms;
    eraseQueryWithAuxPreds(outputRewriting,outputRewritingWithoutAuxAtoms);

    auto eTime = std::chrono::high_resolution_clock::now();
    rewritingDuration = ( eTime - sTime );
    rewritingSize = outputRewritingWithoutAuxAtoms.size();
    return outputRewritingWithoutAuxAtoms;
}

void
XParallelRewrite::mainProcedure(
    vector< XQuery* >* queries,
    XRulesetIterator* rulesetIterator,
    std::vector< XRule* >& output,
    XParallelRewrite* This )
{
    /*******************/
    //hash< thread::id > idHasher;
    //idHasher(this_thread::get_id());
    /*******************/
    assert_msg( queries != NULL, "Null query vector in input" );
    // The input queries are not to be added to the output of this function, since they have already been added to the final rewriting.
    vector< XQuery* > workingQueue(*queries);
    size_t oldSize = 0;
    size_t currentSize = workingQueue.size();
    while( currentSize > oldSize )
    {
        trace_msg( rewriting, 1, "Iteration i^th:" );
        size_t i = oldSize;
        oldSize = workingQueue.size();
        for( ; i<currentSize; i++ )
        {
            assert_msg( workingQueue[i] != NULL, "Null query" );
            assert_msg( workingQueue[i]->getQueryRule() != NULL, "Null query rule" );
            const XQuery& query = *(workingQueue[i]);
            trace_msg( rewriting, 2, "Analyzing query " << *(query.getQueryRule()) );
            // If the input query is atomic it is rewritten immediately, a splitability check is carried out otherwise.
            // If the query is splittable, a fresh query is generated for each independent component.
            // If the query is not splittable, it is managed by function rewriteConjunctiveQuery.
            if( query.isAtomic() )
            {
                This->rewriteQuery(query,rulesetIterator,workingQueue);
            }
            else if( query.getSharedNulls().size() > 0 )
            {
                This->manageConjunctiveQuery(query,rulesetIterator,workingQueue,output,This);
            }
            else
            {
                vector< XQuery* > splitQuery;
                bool isSplittable = This->existentialJoinDecomposition(query,splitQuery);
                if( isSplittable )
                {
                    assert_msg( splitQuery.size() > 0, "The query has not correctly been split up" );
                    vector< thread > threads;
                    // Reminder: the last query in vector 'splitQuery' is the merging query, thus it is not to be rewritten;
                    for( unsigned j=0; j<splitQuery.size()-1; j++ )
                    {
                        assert_msg( splitQuery[j] != NULL, "Null query" );
                        assert_msg( splitQuery[j]->getQueryRule() != NULL, "Null query rule" );

                        This->lockOutputRewriting();
                        output.push_back(splitQuery[j]->getQueryRule());
                        This->unlockOutputRewriting();

                        vector< XQuery* >* threadInputQuery = new vector< XQuery* >();
                        threadInputQuery->push_back(splitQuery[j]);
                        // Every thread needs to receive its own iterator.
                        assert_msg( dynamic_cast< XRulesetIteratorStandard* >(rulesetIterator) != NULL, "This should be a standard iterator" );
                        XRulesetIterator* threadRuleset = new XRulesetIteratorStandard(*(dynamic_cast< XRulesetIteratorStandard* >(rulesetIterator)));
                        // If a thread from the pool is available, run it. Rewrite the current component by yourself, otherwise.
                        This->lockActiveThreads();
                        if( This->activeThreads < This->nCores )
                        {
                            This->activeThreads++;
                            This->unlockActiveThreads();
                            threads.push_back(thread(&XParallelRewrite::mainProcedure,This,threadInputQuery,threadRuleset,std::ref(output),This));
                        }
                        else
                        {
                            This->unlockActiveThreads();
                            This->mainProcedure(threadInputQuery,threadRuleset,output,This);
                        }
                    }
                    for( unsigned j=0; j<threads.size(); j++ )
                    {
                        threads[j].join();
                        This->lockActiveThreads();
                        This->activeThreads--;
                        This->unlockActiveThreads();
                    }

                    This->lockOutputRewriting();
                    output.push_back(splitQuery.back()->getQueryRule());
                    This->unlockOutputRewriting();
                    delete splitQuery[splitQuery.size()-1];
                }
                else
                {
                    trace_msg( rewriting, 2, "The query is not decomposable" );
                    // The query has not been decomposed, but the set of shared nulls has been computed
                    // and it has been stored into a new query (splitQuery[0]) which points to the same rule pointed by 'query'.
                    assert_msg( splitQuery.size() == 1, "The query is not decomposable" );
                    assert_msg( splitQuery[0] != NULL, "Null query" );
                    assert_msg( splitQuery[0]->getQueryRule() != NULL, "Null query rule" );
                    This->manageConjunctiveQuery(*splitQuery[0],rulesetIterator,workingQueue,output,This);
                    delete splitQuery[0];
                }
            }
        }
        currentSize = workingQueue.size();
    }

    for( unsigned i=0; i<queries->size(); i++ )
    {
        assert_msg( i < workingQueue.size(), "Index out of range" );
        assert_msg( workingQueue[i] != NULL, "Null query" );
        delete workingQueue[i];
    }
    for( unsigned i=queries->size(); i<workingQueue.size(); i++ )
    {
        assert_msg( workingQueue[i] != NULL, "Null query" );
        This->lockOutputRewriting();
        output.push_back(workingQueue[i]->getQueryRule());
        This->unlockOutputRewriting();
        delete workingQueue[i];
    }
//    if( workingQueue.size() > queries.size() )
//    {
//        vector< pthread_t > threads(workingQueue.size(),pthread_t());
//        vector< ThreadData > threadArgs(workingQueue.size(),ThreadData());
//        // Our homomorphism check has been already carried out (the map of canonically-renamed queries is shared).
//        for( unsigned r=0; r<workingQueue.size(); r++ )
//        {
//            lockOutputRewriting();
//            output.push_back(workingQueue[r]);
//            unlockOutputRewriting();
//
//            // Run a new thread on the current query.
//            vector< XRule* >* threadInput = new vector< XRule*>();
//            threadInput->push_back(workingQueue[r]);
//            // Every thread has to receive its own iterator.
//            XRulesetIterator* threadRuleset = NULL;
//            if( XRulesetIteratorStandard* ptr = dynamic_cast< XRulesetIteratorStandard* >(rulesetIterator) )
//                threadRuleset = new XRulesetIteratorStandard(*ptr);
//            else if( XRulesetIteratorSub* ptr = dynamic_cast< XRulesetIteratorSub* >(rulesetIterator) )
//                threadRuleset = new XRulesetIteratorSub(*ptr);
//            else if( XRulesetIteratorNonSub* ptr = dynamic_cast< XRulesetIteratorNonSub* >(rulesetIterator) )
//                threadRuleset = new XRulesetIteratorNonSub(*ptr);
//            assert_msg( threadRuleset != NULL, "Null ruleset iterator!" );
//            assert_msg( r < threadArgs.size(), "Index out of range" );
//            threadArgs[r].This = this;
//            threadArgs[r].queries = threadInput;
//            threadArgs[r].ruleset = threadRuleset;
//            threadArgs[r].output = &output;
//
//            pthread_attr_t threadAttr;
//            pthread_attr_init(&threadAttr);
//            pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_JOINABLE);
//            int rc = pthread_create(&threads[r],&threadAttr,threadEntryFunction,(void*)&threadArgs[r]);
//            if( rc )
//            {
//               cerr << "ERROR; return code from pthread_create() is " << rc << endl;
//               exit(-1);
//            }
//            pthread_attr_destroy(&threadAttr);
//        }
//        // Wait until all the threads stop!!!
//        for( unsigned t=0; t<threads.size(); t++ )
//        {
//            void* returnStatus;
//            int rc = pthread_join(threads[t], &returnStatus);
//            if( rc )
//            {
//                cerr << "ERROR; return code from pthread_join() is " << rc << endl;
//                exit(-1);
//            }
//            trace_msg( rewriting, 3, "Thread " << threads[t] << ": work completed!" );
//        }
//    }
    delete queries;
    delete rulesetIterator;
}

void
XParallelRewrite::rewriteQuery(
    const XQuery& query,
    XRulesetIterator* rulesetIterator,
    vector< XQuery* >& workingQueue )
{
    assert_msg( query.getQueryRule() != NULL, "Null query rule" );
    assert_msg( query.getQueryRule()->getBody() != NULL, "Null body" );
    assert_msg( query.getQueryRule()->getHead() != NULL, "Null head" );
    assert_msg( query.getQueryRule()->getHead()->size() == 1, "Query rules with more than one head atom are not allowed" );
    // TODO: Fix statistics-variables..
//    auto sTime = std::chrono::high_resolution_clock::now();
//    assert_msg( inputProgram.getQuery() != NULL, "The input query is null." );
    // TODO: Fix tracing..
//    trace_msg( rewriting, 1, "Start by adding the input query rules to the final rewriting: " );
    const XRule& queryRule = *(query.getQueryRule());
    while( rulesetIterator->hasNext() )
    {
        const XRule& rule = rulesetIterator->next();
        trace_msg( rewriting, 2, "Computing single-piece unifiers between " << queryRule << " and " << rule );
        std::list< XRule > tmpRules4AggrUnifiers;
        // NOTICE: This function is responsible for the deallocation of the following pointers.
        vector< XPieceUnifier* > SPU = computeSPU(queryRule,rule);
        // Extend SPU by computing the set of all single-piece aggregators of the
        // input query with the starting set of TGDs.
        computeSPUAggregators(SPU,tmpRules4AggrUnifiers);
        // Now, apply SPUs in order to produce new rewriting rules.
        for( unsigned x=0; x<SPU.size(); x++ )
        {
            assert_msg( SPU[x] != NULL, "Null unifier" );
            XRule* rewrittenRule = produceRewritingByPieceUnifier(*(SPU[x]));
            pushQuery(rewrittenRule,workingQueue);
            delete SPU[x];
        }
        // Delete the aggregated rules added to the program in order to compute the aggregated single piece unifiers.
        tmpRules4AggrUnifiers.clear();
    }
    rulesetIterator->reset();
//    auto eTime = std::chrono::high_resolution_clock::now();
//    rewritingDuration = ( eTime - sTime );
//    rewritingSize = finalRewritingWithoutAuxAtoms.size();
}

void
XParallelRewrite::manageConjunctiveQuery(
    const XQuery& query,
    XRulesetIterator* rulesetIterator,
    std::vector< XQuery* >& workingQueue,
    vector< XRule* >& output,
    XParallelRewrite* This )
{
    assert_msg( query.getQueryRule() != NULL, "Null query rule" );
    assert_msg( query.getQueryRule()->getBody() != NULL, "Null body" );
    assert_msg( query.getQueryRule()->getHead() != NULL, "Null head" );
    assert_msg( query.getSharedNulls().size() > 0, "Conjunctive query with no shared nulls" );
    const XRule& queryRule = *(query.getQueryRule());
    const XBody* queryRuleBody = queryRule.getBody();
    assert_msg( queryRuleBody != NULL, "Null body" );
    // Break the query in single atomic queries.
    vector< XQuery* > splitQuery;
    vector< XLiteral > mergeRuleBodyLiterals;
    for( unsigned i=0; i<queryRuleBody->size(); i++)
    {
        XRandomAccessSet< unsigned > subQueryAtomPositions;
        subQueryAtomPositions.pushItem(i);
        XQuery* subQueryRule = inputProgram.createQuery(generateSubQuery(queryRule,subQueryAtomPositions,mergeRuleBodyLiterals));
        splitQuery.push_back(subQueryRule);
    }
    if( mergeRuleBodyLiterals.size() > 0 )
    {
        // The variable renaming is not needed here since the following rule is not gonna be rewritten.
        const XHead* queryRuleHead = queryRule.getHead();
        assert_msg( queryRuleHead != NULL, "Null head" );
        assert_msg( queryRuleHead->isAtomic(), "Non-atomic head" );
        XHead* mergeQueryRuleHead = inputProgram.createAtomicHead(queryRuleHead->at(0));
        XBody* mergeQueryRuleBody = inputProgram.createBody(mergeRuleBodyLiterals);
        XRule* mergeQueryRule = inputProgram.createRule(mergeQueryRuleHead,mergeQueryRuleBody);
        XQuery* mergeQuery = inputProgram.createQuery(mergeQueryRule);
        trace_msg( rewriting, 2, "The reconciliation rule is " << *mergeQueryRule );
        // This query mustn't be rewritten since its body predicates do not belong to the input program.
        splitQuery.push_back(mergeQuery);
    }

    /**
     * Spezza la query in ogni posizione, tanto ne devi creare tante atomiche, e genera le sottoquery insieme a quella di merging
     * mediante la funzione generateSubQuery (vedi chiamata in existentialJoinDecomposition). Dopodichè prova a lanciare un thread
     * per ogni componente, ma fai attenzione: 1) escludi dal ruleset le regole che causano la join esistenziale; 2) l'output che
     * produrrà il thread in questo caso non dovrà confluire in quello generale ma dovrà essere conservato localmente visto che poi
     * lo dovrai usare per l'unfolding. Una volta che tutti i thread hanno concluso, fai l'unfolding tenendo conto di tutti gli output
     * restituiti dai thread e poi inserisci questi output nel rewriting finale (e non nella coda di lavoro, perchè tanto non dovranno
     * essere ulteriormente riscritte). Una volta ottenuto l'unfolding, dallo in input ad una chiamata ricorsiva di mainProcedure
     * con ruleset quello formato dalle sole regole esistenziali che causano la join. Anche in questo caso l'output della chiamata
     * ricorsiva andrà conservato localmente, infatti una volta che la chiamata ricorsiva termina, tale output andrà inserito nella
     * coda di lavoro. A quel punto la funzione può ritornare, in modo che l'algoritmo continui a lavorare da dove si era fermato.
     *
     */
    /**
     * Per fare l'unfolding predisponi un list< vector< XRule* > > con i risultati delle riscritture delle singole query atomiche;
     * poi crea una mappa <index_t,iterator> che metta in corrispondenza il predIdx della testa di ogni query atomica con il risultato
     * della riscrittura di quella query; infine devi prevedere anche un vector con i predIdx delle teste delle query atomiche.
     * Per la procedura sarà necessario tenere traccia dell'insieme di regole unfoldate al passo precedente e quello corrente.
     * La procedura dovrà essere strutturata come segue: triplo for innestato, il primo sui predIdx delle query atomiche, il secondo
     * sull'insieme di regole unfoldate ottenuto al passo precedente ed il terzo sui risultati del predIdx corrente; ad ogni iterazione
     * dovrai prendere la posizione nel corpo della regola corrente del predIdx corrente e sostituirlo con il corpo della regola
     * del risultato corrente; aggiungi il risultato all'unfolding corrente; alla fine del for butta l'unfolding ottenuto al passo
     * precedente e fai diventare quello corrente come quello ottenuto al passo precedente; alla fine l'unfolding finale sarà il tuo risultato.
     */

    assert_msg( splitQuery.size() > 0, "The query has not correctly been split up" );
    vector< thread > threads;
    RESULT_SETS partialResults;
    unordered_map< index_t, RESULT_SETS::const_iterator > predIdx2ResultSet;
    vector< index_t > queryPredIndices;

    // Reminder: the last query in vector 'splitQuery' is the merging query, thus it is not to be rewritten;
    for( unsigned j=0; j<splitQuery.size()-1; j++ )
    {
        assert_msg( splitQuery[j] != NULL, "Null query" );
        assert_msg( splitQuery[j]->getQueryRule() != NULL, "Null query rule" );
        assert_msg( splitQuery[j]->getQueryRule()->getHead() != NULL, "Null query head" );
        assert_msg( splitQuery[j]->getQueryRule()->getHead()->isAtomic(), "Not valid query head" );

        RESULT_SETS::iterator itCurrentResult = partialResults.insert(partialResults.end(),vector< XRule* >());
        index_t headIdx = splitQuery[j]->getQueryRule()->getHead()->at(0).getPredIndex();
        queryPredIndices.push_back(headIdx);
        predIdx2ResultSet.insert(pair< index_t, RESULT_SETS::const_iterator >(headIdx,itCurrentResult));
        itCurrentResult->push_back(splitQuery[j]->getQueryRule());

        vector< XQuery* >* threadInputQuery = new vector< XQuery* >();
        threadInputQuery->push_back(splitQuery[j]);
        // Every thread needs to receive its own iterator.
        // FIXME: the ruleset iterator which is gonna be created relies on the full program ruleset, is it ok?
        XRulesetIterator* threadRuleset = new XRulesetIteratorNonSub(inputProgram);
        for( unsigned i=0; i<query.getSharedNulls().size(); i++ )
        {
            threadRuleset->pushIterator(inputProgram.getRuleIntroducingNullIdx(query.getSharedNulls().at(i)));
        }
        // If a thread from the pool is available, run it. Rewrite the current component by yourself, otherwise.
        This->lockActiveThreads();
        if( This->activeThreads < This->nCores )
        {
            This->activeThreads++;
            This->unlockActiveThreads();
            threads.push_back(thread(&XParallelRewrite::mainProcedure,This,threadInputQuery,threadRuleset,std::ref(*itCurrentResult),This));
        }
        else
        {
            This->unlockActiveThreads();
            This->mainProcedure(threadInputQuery,threadRuleset,*itCurrentResult,This);
        }
    }
    for( unsigned j=0; j<threads.size(); j++ )
    {
        threads[j].join();
        This->lockActiveThreads();
        This->activeThreads--;
        This->unlockActiveThreads();
    }
    // Remainder: the merging query is the last one.
    RESULT_SETS::iterator itMergingQuery = partialResults.insert(partialResults.end(),vector< XRule* >());
    index_t headIdx = splitQuery.back()->getQueryRule()->getHead()->at(0).getPredIndex();
    queryPredIndices.push_back(headIdx);
    predIdx2ResultSet.insert(pair< index_t, RESULT_SETS::const_iterator >(headIdx,itMergingQuery));
    itMergingQuery->push_back(splitQuery.back()->getQueryRule());
    delete splitQuery[splitQuery.size()-1];

    // These queries need to be destroyed right after they are rewritten.
    vector< XQuery* >* unfolding = This->unfold(partialResults,predIdx2ResultSet,queryPredIndices);

    // Push partial results into the output vector, since those queries should not be rewritten anymore.
    for( RESULT_SETS::const_iterator it=partialResults.begin(); it != partialResults.end(); it++ )
        for( unsigned j=0; j<it->size(); j++ )
        {
            assert_msg( it->at(j) != NULL, "Null query" );
            This->lockOutputRewriting();
            output.push_back(it->at(j));
            This->unlockOutputRewriting();
        }

    // FIXME: the ruleset iterator which is gonna be created relies on the rules introducing the shared nulls, is it ok?
    XRulesetIterator* unfoldingRuleset = new XRulesetIteratorSub(inputProgram);
    for( unsigned i=0; i<query.getSharedNulls().size(); i++ )
    {
        unfoldingRuleset->pushIterator(inputProgram.getRuleIntroducingNullIdx(query.getSharedNulls().at(i)));
    }
    // Push the final result into the working queue and let the caller go on.
    for( unsigned i=0; i<unfolding->size(); i++ )
    {
        This->rewriteQuery(*unfolding->at(i),unfoldingRuleset,workingQueue);
        delete unfolding->at(i)->getQueryRule();
        delete unfolding->at(i);
    }
    delete unfolding;
    delete unfoldingRuleset;
}

bool
XParallelRewrite::existentialJoinDecomposition(
    const XQuery& query,
    vector< XQuery* >& splitQuery )
{
    assert_msg( query.getQueryRule() != NULL, "Null query rule" );
    const XRule& queryRule = *(query.getQueryRule());
    bool isDecomposable = false;
    // Try to split the query. If you manage to do that, do not forget to add a merging rule.
    const XBody* queryRuleBody = queryRule.getBody();
    assert_msg( queryRuleBody != NULL, "Null body" );

    vector< XLiteral > mergeQueryRuleBodyLiterals;
    unordered_set< unsigned > checkedBodyPositions;
    for( unsigned x=0; x<queryRuleBody->size() && checkedBodyPositions.size()<queryRuleBody->size(); x++ )
    {
        pair< unordered_set< unsigned >::const_iterator, bool > par = checkedBodyPositions.insert(x);
        if( par.second )
        {
            XRandomAccessSet< index_t > sharedNulls;
            XRandomAccessSet< unsigned > subQueryAtomPositions;
            subQueryAtomPositions.pushItem(x);
            for( unsigned y=0; y<subQueryAtomPositions.size(); y++ )
            {
                checkedBodyPositions.insert(subQueryAtomPositions[y]);
                checkExistentialJoins(queryRule,subQueryAtomPositions[y],subQueryAtomPositions,sharedNulls);
            }
            // If joinAtomsPositions has got the same size as the query body, the current query is
            // composed by a unique conjunctive component, else the input query is decomposable and
            // the current component may be either atomic or conjunctive.
            if( subQueryAtomPositions.size() < queryRuleBody->size() )
            {
                isDecomposable = true;
                trace_msg( rewriting, 2, "Existential join-decomposition..." );
                XRule* subQueryRule = generateSubQuery(queryRule,subQueryAtomPositions,mergeQueryRuleBodyLiterals);
                XQuery* subQuery = inputProgram.createQuery(subQueryRule,sharedNulls);
                // No need to check the existence of homomorphic queries since the head of this query is completely new.
                // No need to carry out the query-elimination optimization check since the body of this query is atomic.
                splitQuery.push_back(subQuery);
            }
            else
            {
                XQuery* inputQueryWithSharedNulls = inputProgram.createQuery(query.getQueryRule(),sharedNulls);
                splitQuery.push_back(inputQueryWithSharedNulls);
            }
        }
    }
    if( mergeQueryRuleBodyLiterals.size() > 0 )
    {
        // The variable renaming is not needed here since the following rule is not gonna be rewritten.
        const XHead* queryRuleHead = queryRule.getHead();
        assert_msg( queryRuleHead != NULL, "Null head" );
        assert_msg( queryRuleHead->isAtomic(), "Non-atomic head" );
        XHead* mergeQueryRuleHead = inputProgram.createAtomicHead(queryRuleHead->at(0));
        XBody* mergeQueryRuleBody = inputProgram.createBody(mergeQueryRuleBodyLiterals);
        XRule* mergeQueryRule = inputProgram.createRule(mergeQueryRuleHead,mergeQueryRuleBody);
        XQuery* mergeQuery = inputProgram.createQuery(mergeQueryRule);
        trace_msg( rewriting, 2, "The reconciliation rule is " << *mergeQueryRule );
        // This query mustn't be rewritten since its body predicates do not belong to the input program.
        splitQuery.push_back(mergeQuery);
    }
    return isDecomposable;
}

void
XParallelRewrite::checkExistentialJoins(
    const XRule& queryRule,
    unsigned currentLiteralPos,
    XRandomAccessSet< unsigned >& subQueryAtomPositions,
    XRandomAccessSet< index_t >& sharedNulls ) const
{
    // For each term from the current literal and for each (body) position where it occurs
    // check whether such a position is relative to a different atom and whether an existential-join may hold.
    assert_msg( queryRule.getBody() != NULL, "Null body" );
    assert_msg( currentLiteralPos < queryRule.getBody()->size(), "Index out of range" );
    const XNullsetTable& nullsetTable = inputProgram.getPredicateNullsets();
    const XLiteral& currentLiteral = queryRule.getBody()->at(currentLiteralPos);
    trace_msg( rewriting, 2, "Check whether literal " << currentLiteral << " has got some existential-joins."  );
    for( unsigned i=0; i<currentLiteral.getTerms().size(); i++ )
    {
        const XTerm& currentTerm = currentLiteral.getTerms().at(i);
        for( unsigned j=0; j<queryRule.getBodyPositions(currentTerm).size(); j++ )
        {
            unsigned joinLiteralPos = queryRule.getBodyPositions(currentTerm).at(j).atomPos;
            unsigned joinTermPos = queryRule.getBodyPositions(currentTerm).at(j).termPos;
            assert_msg( joinLiteralPos < queryRule.getBody()->size(), "Index out of range" );
            assert_msg( joinTermPos < queryRule.getBody()->at(joinLiteralPos).getTerms().size(), "Index out of range" );
            // The previous literals have been already processed, so consider just the following ones
            // (which might belong to another sub-query). Anyway, given two atoms, a1 and a2, if a1 has got
            // an existential join with a2, then a2 has got an existential join with a1.
            // Thus, no problems if literals from the other sub-queries are considered here.
            if( joinLiteralPos > currentLiteralPos )
            {
                const XLiteral& joinLiteral = queryRule.getBody()->at(joinLiteralPos);
                const XNullset& currentPositionNullset = nullsetTable.at(currentLiteral.getPredIndex()).at(i);
                const XNullset& joinPositionNullset = nullsetTable.at(joinLiteral.getPredIndex()).at(joinTermPos);
                for( unsigned k=0; k<currentPositionNullset.size(); k++ )
                {
                    if( joinPositionNullset.find(currentPositionNullset[k]) )
                    {
                        trace_msg( rewriting, 3, "An existential-join (null_id: " << currentPositionNullset[k] << ")" <<
                                " may hold between " << joinLiteral << "_" << joinTermPos << " and " << currentLiteral << "_" << i );
                        sharedNulls.pushItem(currentPositionNullset[k]);
                        subQueryAtomPositions.pushItem(joinLiteralPos);
                    }
                }
            }
        }
    }
}

XRule*
XParallelRewrite::generateSubQuery(
    const XRule& query,
    const XRandomAccessSet< unsigned >& subQueryAtomPositions,
    vector< XLiteral >& mergeQueryBodyLiterals )
{
    const XBody* queryBody = query.getBody();
    assert_msg( queryBody != NULL, "Null body" );
    stringstream ss;
    // Compute the set of terms which are gonna be included by the head.
    vector< XTerm > subQueryHeadTerms;
    vector< XLiteral > subQueryBodyLiterals;
    vector< XTerm > mergeQueryBodyAtomTerms;
    // The subquery needs to be renamed since it will be processed by the rewriting algorithm.
    // The same does not hold for the merging query, which will not be rewritten.
    XMapping renaming;
    for( unsigned i=0; i<subQueryAtomPositions.size(); i++ )
    {
        const XLiteral& literal = queryBody->at(subQueryAtomPositions[i]);
        vector< XTerm > subQueryBodyAtomTerms;
        for( unsigned j=0; j<literal.getTerms().size(); j++ )
        {
            const XTerm& term = literal.getTerms().at(j);
            if( term.isStandardVar() )
            {
                XMapping::const_iterator it = renaming.find(term);
                if( it == renaming.end() )
                {
                    stringstream ss;
                    lockProgramVariableCounter();
                    inputProgram.incrementVariablesCounter();
                    ss << "X" << inputProgram.getVariablesCounter();
                    unlockProgramVariableCounter();
                    XTerm* renamedTerm = inputProgram.createStandardVariable(ss.str());
                    renaming.insert(pair< const XTerm&, const XTerm& >(term,*renamedTerm));
                    subQueryBodyAtomTerms.push_back(*renamedTerm);
                    // Include the current variable in the head if it is a distinguished variable from the original query
                    // (i.e., it belongs to the head or occurs in a body literal other than the ones belonging to the current subquery).
                    if( query.getHeadOccurrences(term) > 0 )
                    {
                        subQueryHeadTerms.push_back(*renamedTerm);
                        mergeQueryBodyAtomTerms.push_back(term);
                    }
                    else
                    {
                        bool isShared = false;
                        for( unsigned x=0; x<query.getBodyPositions(term).size() && !isShared; x++ )
                            if( !subQueryAtomPositions.find(query.getBodyPositions(term).at(x).atomPos) )
                            {
                                isShared = true;
                                subQueryHeadTerms.push_back(*renamedTerm);
                                mergeQueryBodyAtomTerms.push_back(term);
                            }
                    }
                    delete renamedTerm;
                }
                else
                {
                    subQueryBodyAtomTerms.push_back(it->second);
                }
            }
            else
            {
                subQueryBodyAtomTerms.push_back(literal.getTerms().at(j));
            }
        }
        XAtom* subQueryBodyAtom = inputProgram.createAtom(literal.getPredIndex(),subQueryBodyAtomTerms,literal.getAtom().isTrueNegated());
        XLiteral* subQueryBodyLiteral = inputProgram.createLiteral(*subQueryBodyAtom,literal.isNaf());
        subQueryBodyLiterals.push_back(*subQueryBodyLiteral);
        delete subQueryBodyAtom;
        delete subQueryBodyLiteral;
    }
    lockQueryPredIdx();
    ss << QUERY_ANS << queryPredIdx++;
    pair< index_t, bool > resSubQueryPred = inputProgram.addPredicate(ss.str(),subQueryHeadTerms.size());
    unlockQueryPredIdx();
    // queryHeadAtom should include all the terms appearing in the body, which may be a conjunction.
    XAtom* subQueryHeadAtom = inputProgram.createAtom(resSubQueryPred.first,subQueryHeadTerms);
    XHead* subQueryHead = inputProgram.createAtomicHead(*subQueryHeadAtom);
    delete subQueryHeadAtom;
    XBody* subQueryBody = inputProgram.createBody(subQueryBodyLiterals);
    XRule* subQueryRule = inputProgram.createRule(subQueryHead,subQueryBody);
    trace_msg( rewriting, 2, "The generated existentially-decomposed sub-query is " << *subQueryRule );
    // Before returning update mergeQueryBodyLits
    XAtom* mergeQueryBodyAtom = inputProgram.createAtom(resSubQueryPred.first,mergeQueryBodyAtomTerms);
    XLiteral* mergeQueryBodyLiteral = inputProgram.createLiteral(*mergeQueryBodyAtom);
    mergeQueryBodyLiterals.push_back(*mergeQueryBodyLiteral);
    trace_msg( rewriting, 2, "Add " << *mergeQueryBodyLiteral << " to the merging rule." );
    delete mergeQueryBodyAtom;
    delete mergeQueryBodyLiteral;

    return subQueryRule;
}

//void*
//XParallelRewrite::threadEntryFunction(
//    void* args )
//{
//    ThreadData* data = (ThreadData*)args;
//    XParallelRewrite* This = data->This;
//    vector< XRule* >* queries = data->queries;
//    XRulesetIterator* rulesetIterator = data->ruleset;
//    vector< XRule* >* output = data->output;
//    assert_msg( ( This != NULL && queries != NULL && rulesetIterator != NULL && output != NULL ), "Null input" );
//    This->mainProcedure(*queries,rulesetIterator,*output);
//    delete queries;
//    delete rulesetIterator;
//    pthread_exit(NULL);
//}

void
XParallelRewrite::pushQuery(
    XRule* rewriting,
    vector< XQuery* >& workingQueue )
{
    // Check whether the generated rule is homomorphic to an existent one.
    bool isNecessary = !isUnnecessary(*rewriting);
    if( isNecessary )
    {
        // Finally, if the produced rule passes previous checks it is added to the final
        // rewriting, but just after being minimized by the query elimination strategy.
        XRule* optimizedQuery = queryElimination(*rewriting);
        if( optimizedQuery != NULL )
        {
            delete rewriting;
            // The optimized query may be different from the original one, so an additional check is required.
            bool isOptimizedQueryNecessary = !isUnnecessary(*optimizedQuery);
            if( isOptimizedQueryNecessary )
            {
                trace_msg( rewriting, 1, "Add query rule: " << *optimizedQuery );
                workingQueue.push_back(inputProgram.createQuery(optimizedQuery));
            }
            else
            {
                trace_msg( rewriting, 1, "Do not add query: " << *optimizedQuery );
                delete optimizedQuery;
            }
        }
        else
        {
            trace_msg( rewriting, 1, "Add query: " << *rewriting );
            workingQueue.push_back(inputProgram.createQuery(rewriting));
        }
    }
    else
    {
        trace_msg( rewriting, 1, "Do not add query: " << *rewriting );
        delete rewriting;
    }
}

vector< XQuery* >*
XParallelRewrite::unfold(
    const RESULT_SETS& resultSets,
    const unordered_map< index_t, RESULT_SETS::const_iterator >& predIdx2ResultSet,
    const vector< index_t >& queryPredIndices )
{
    /**
     * Per fare l'unfolding predisponi un list< vector< XRule* > > con i risultati delle riscritture delle singole query atomiche;
     * poi crea una mappa <index_t,iterator> che metta in corrispondenza il predIdx della testa di ogni query atomica con il risultato
     * della riscrittura di quella query; infine devi prevedere anche un vector con i predIdx delle teste delle query atomiche.
     * Per la procedura sarà necessario tenere traccia dell'insieme di regole unfoldate al passo precedente e quello corrente.
     * La procedura dovrà essere strutturata come segue: triplo for innestato, il primo sui predIdx delle query atomiche, il secondo
     * sull'insieme di regole unfoldate ottenuto al passo precedente ed il terzo sui risultati del predIdx corrente; ad ogni iterazione
     * dovrai prendere la posizione nel corpo della regola corrente del predIdx corrente e sostituirlo con il corpo della regola
     * del risultato corrente; aggiungi il risultato all'unfolding corrente; alla fine del for butta l'unfolding ottenuto al passo
     * precedente e fai diventare quello corrente come quello ottenuto al passo precedente; alla fine l'unfolding finale sarà il tuo risultato.
     */
    vector< XQuery* >* result = new vector< XQuery* >();
    queue< XRule* > ruleQueue;
    // The first rule is the merging rule.
    XRule* mergingRule = new XRule(*(resultSets.back().front()));
    ruleQueue.push(mergingRule);

    while( !ruleQueue.empty() )
    {
        XRule* rule = ruleQueue.front();
        ruleQueue.pop();
        assert_msg( rule != NULL, "Null rule" );
        assert_msg( rule->getBody() != NULL, "Null rule body" );

        // Check whether the current rule has been fully unfolded or not.
        const XBody& body = *(rule->getBody());
        unordered_map< index_t, RESULT_SETS::const_iterator >::const_iterator mapIt = predIdx2ResultSet.end();
        for( unsigned i=0; i<body.size() && mapIt==predIdx2ResultSet.end(); i++ )
        {
            // If the current literal belongs to a predicate name whose index is one of the map keys, the query is not fully unfolded.
            mapIt = predIdx2ResultSet.find(body[i].getPredIndex());
            if( mapIt != predIdx2ResultSet.end() )
            {
                const vector< XRule* >& ruleset = *(mapIt->second);
                for( unsigned j=0; j<ruleset.size(); j++ )
                {
                    XRule* unfoldedRule = unfoldingStep(*rule,i,*ruleset[j]);
                    ruleQueue.push(unfoldedRule);
                }
            }
        }
        if( mapIt == predIdx2ResultSet.end() )
            result->push_back(inputProgram.createQuery(rule));
        else
            delete rule;
    }
    return result;
}

XRule*
XParallelRewrite::unfoldingStep(
    const XRule& queryToBeUnfolded,
    unsigned literalPos,
    const XRule& unfoldingRule )
{
    // Variable renaming is needed in order to avoid clutters among variable names.
    assert_msg( queryToBeUnfolded.getHead() != NULL, "Null head" );
    assert_msg( queryToBeUnfolded.getHead()->isAtomic(), "Non atomic head" );
    assert_msg( queryToBeUnfolded.getBody() != NULL, "Null body" );

    // Head renaming.
    const XAtom& headAtomToBeUnfolded = queryToBeUnfolded.getHead()->at(0);
    XMapping renaming;
    vector< XTerm > unfoldedHeadAtomTerms;
    for( unsigned i=0; i<headAtomToBeUnfolded.getTerms().size(); i++ )
    {
        const XTerm& termToBeUnfolded = headAtomToBeUnfolded.getTerms().at(i);
        if( termToBeUnfolded.isStandardVar() )
        {
            XMapping::const_iterator it = renaming.find(termToBeUnfolded);
            if( it == renaming.end() )
            {
                stringstream ss;
                lockProgramVariableCounter();
                inputProgram.incrementVariablesCounter();
                ss << "X" << inputProgram.getVariablesCounter();
                unlockProgramVariableCounter();
                XTerm* renamedTerm = inputProgram.createStandardVariable(ss.str());
                renaming.insert(pair< const XTerm&, const XTerm& >(termToBeUnfolded,*renamedTerm));
                unfoldedHeadAtomTerms.push_back(*renamedTerm);
                delete renamedTerm;
            }
            else
                unfoldedHeadAtomTerms.push_back(it->second);
        }
        else
            unfoldedHeadAtomTerms.push_back(termToBeUnfolded);
    }
    XAtom* unfoldedHeadAtom = inputProgram.createAtom(headAtomToBeUnfolded.getPredIndex(),unfoldedHeadAtomTerms);
    XHead* unfoldedHead = inputProgram.createAtomicHead(*unfoldedHeadAtom);
    delete unfoldedHeadAtom;

    // Body renaming and unfolding.
    const XBody* bodyToBeUnfolded = queryToBeUnfolded.getBody();
    vector< XLiteral > unfoldedBodyLiterals;
    for( unsigned i=0; i<bodyToBeUnfolded->size(); i++ )
    {
        const XLiteral& literalToBeUnfolded = bodyToBeUnfolded->at(i);
        if( i != literalPos )
        {
            // Rename variables
            vector< XTerm > unfoldedBodyLiteralTerms;
            for( unsigned j=0; j<literalToBeUnfolded.getTerms().size(); j++ )
            {
                const XTerm& termToBeUnfolded = literalToBeUnfolded.getTerms().at(j);
                if( termToBeUnfolded.isStandardVar() )
                {
                    XMapping::const_iterator it = renaming.find(termToBeUnfolded);
                    if( it == renaming.end() )
                    {
                        stringstream ss;
                        lockProgramVariableCounter();
                        inputProgram.incrementVariablesCounter();
                        ss << "X" << inputProgram.getVariablesCounter();
                        unlockProgramVariableCounter();
                        XTerm* renamedTerm = inputProgram.createStandardVariable(ss.str());
                        renaming.insert(pair< const XTerm&, const XTerm& >(termToBeUnfolded,*renamedTerm));
                        unfoldedBodyLiteralTerms.push_back(*renamedTerm);
                        delete renamedTerm;
                    }
                    else
                        unfoldedBodyLiteralTerms.push_back(it->second);
                }
                else
                    unfoldedBodyLiteralTerms.push_back(termToBeUnfolded);
            }
            XAtom* unfoldedBodyAtom = inputProgram.createAtom(
                    literalToBeUnfolded.getPredIndex(),unfoldedBodyLiteralTerms,literalToBeUnfolded.getAtom().isTrueNegated());
            XLiteral* unfoldedBodyLiteral = inputProgram.createLiteral(*unfoldedBodyAtom,literalToBeUnfolded.isNaf());
            unfoldedBodyLiterals.push_back(*unfoldedBodyLiteral);
            delete unfoldedBodyAtom;
            delete unfoldedBodyLiteral;
        }
        else
        {
            assert_msg( unfoldingRule.getHead() != NULL, "Null head" );
            assert_msg( unfoldingRule.getHead()->isAtomic(), "Non atomic head" );
            assert_msg( unfoldingRule.getHead()->at(0).getPredIndex() == literalToBeUnfolded.getPredIndex(), "Invalid unfolding" );
            assert_msg( unfoldingRule.getBody() != NULL, "Null bodyToBeUnfolded" );
            const XAtom& headAtomUnfoldingRule = unfoldingRule.getHead()->at(0);
            XMapping unfoldingRuleRenaming;
            // Unification between the unfolding rule head and the current literal of the query body.
            for( unsigned j=0; j<literalToBeUnfolded.getTerms().size(); j++ )
            {
                assert_msg( j < headAtomUnfoldingRule.getTerms().size(), "Invalid arity" );
                const XTerm& termToBeUnfolded = literalToBeUnfolded.getTerms().at(j);
                const XTerm& unfoldingTerm = headAtomUnfoldingRule.getTerms().at(j);
                // Variables from the unfolding rule head need to be unified with
                // variables from the current literal of the query body. Moreover,
                // variables from the current literal of the query body need to be renamed.
                if( unfoldingTerm.isStandardVar() )
                {
                    // Unification
                    pair < XMapping::const_iterator, bool > ins =
                            unfoldingRuleRenaming.insert(pair< XTerm, XTerm >(unfoldingTerm,termToBeUnfolded));
                    assert_msg( ( ins.second || termToBeUnfolded == ins.first->second ), "Not valid unification" );

                    // Renaming
                    XMapping::const_iterator it = renaming.find(termToBeUnfolded);
                    if( it == renaming.end() )
                    {
                        stringstream ss;
                        lockProgramVariableCounter();
                        inputProgram.incrementVariablesCounter();
                        ss << "X" << inputProgram.getVariablesCounter();
                        unlockProgramVariableCounter();
                        XTerm* renamedTerm = inputProgram.createStandardVariable(ss.str());
                        renaming.insert(pair< const XTerm&, const XTerm& >(termToBeUnfolded,*renamedTerm));
                        delete renamedTerm;
                    }
                }
            }
            const XBody* unfoldingRuleBody = unfoldingRule.getBody();
            for( unsigned j=0; j<unfoldingRuleBody->size(); j++ )
            {
                const XLiteral& unfoldingLiteral = unfoldingRuleBody->at(j);
                vector< XTerm > unfoldedBodyLiteralTerms;
                for( unsigned k=0; k<unfoldingLiteral.getTerms().size(); k++ )
                {
                    const XTerm& unfoldingTerm = unfoldingLiteral.getTerms().at(k);
                    if( unfoldingTerm.isStandardVar() )
                    {
                        XMapping::const_iterator it = unfoldingRuleRenaming.find(unfoldingTerm);
                        if( it == unfoldingRuleRenaming.end() )
                        {
                            stringstream ss;
                            lockProgramVariableCounter();
                            inputProgram.incrementVariablesCounter();
                            ss << "X" << inputProgram.getVariablesCounter();
                            unlockProgramVariableCounter();
                            XTerm* renamedTerm = inputProgram.createStandardVariable(ss.str());
                            unfoldingRuleRenaming.insert(pair< const XTerm&, const XTerm& >(unfoldingTerm,*renamedTerm));
                            // Since renamedTerm has got a fresh name, it does not need to be renamed.
                            renaming.insert(pair< const XTerm&, const XTerm& >(*renamedTerm,*renamedTerm));
                            unfoldedBodyLiteralTerms.push_back(*renamedTerm);
                        }
                        else
                        {
                            XMapping::const_iterator itRenaming = renaming.find(it->second);
                            assert_msg( itRenaming != renaming.end(), "Not valid matching" );
                            unfoldedBodyLiteralTerms.push_back(itRenaming->second);
                        }
                    }
                    else
                    {
                        unfoldedBodyLiteralTerms.push_back(unfoldingTerm);
                    }
                }
                XAtom* unfoldedBodyAtom = inputProgram.createAtom(
                        unfoldingLiteral.getPredIndex(),
                        unfoldedBodyLiteralTerms,
                        unfoldingLiteral.getAtom().isTrueNegated());
                XLiteral* unfoldedBodyLiteral = inputProgram.createLiteral(*unfoldedBodyAtom,unfoldingLiteral.isNaf());
                unfoldedBodyLiterals.push_back(*unfoldedBodyLiteral);
                delete unfoldedBodyLiteral;
                delete unfoldedBodyAtom;
            }
        }
    }
    XBody* unfoldedBody = inputProgram.createBody(unfoldedBodyLiterals);
    XRule* unfoldedRule = inputProgram.createRule(unfoldedHead,unfoldedBody);
    return unfoldedRule;
}
