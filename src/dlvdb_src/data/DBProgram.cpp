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

#include "DBProgram.h"
#include "Metadata.h"
#include "../../util/DBConnection.h"
#include "../queries/QueryObject.h"

using namespace std;
using namespace DLV2::DB;

DBProgram::DBProgram(
    DBConnection& con ):
        predicates(0),
        graph(new LabeledDependencyGraph< DepGraphNoStrategy, index_t >()),
        connection(con)
{
}


DBProgram::DBProgram( 
    const DBProgram& p ):
        predicates(p.predicates),
        connection(p.connection)
{
    // Making a copy of a program might be too expensive.
    // There is no good reason why this structure should be copied.
    assert(0);
    
    for( index_t i=0; i<p.rules.size(); i++ )
    {
        rules.push_back(new DBRule(*p.rules[i]));
    }
    for( index_t i=0; i<p.facts.size(); i++ )
    {
        facts.push_back(new DBRule(*p.facts[i]));
    }
    queryBuilder = new QueryBuilder(*p.queryBuilder);
    for( index_t i=0; i<p.ruleQueries.size(); i++ )
    {
        ruleQueries.push_back(new QueryObject(*p.ruleQueries[i]));
    }
    for( index_t i=0; i<p.factQueries.size(); i++ )
    {
        factQueries.push_back(new QueryObject(*p.factQueries[i]));
    }
    for( SchemaMap::const_iterator it = p.schemaMapping.begin();
            it != p.schemaMapping.end();
            it++ )
    {
        assert_msg( it->second != NULL, "Trying to copy a program with a null metadata." );
        schemaMapping[it->first] = new Metadata(*(it->second));
    }
    for( RuleSetsMap::const_iterator it = ruleSetsMapping.begin();
            it != ruleSetsMapping.end();
            it++ )
    {
        assert_msg( it->second != NULL, "Trying to copy a program with a null subprogram." );
        ruleSetsMapping[it->first] = new DBRuleSet(*(it->second));
    }
    graph = new LabeledDependencyGraph< DepGraphNoStrategy, index_t >(*p.graph);
}

DBProgram::~DBProgram()
{
    if( graph != NULL )
        delete graph;
    for( RuleSetsMap::iterator it = ruleSetsMapping.begin();
            it != ruleSetsMapping.end();
            it++ )
    {
        assert_msg( it->second != NULL, "Trying to destroy a program with a null subprogram." );
        delete it->second;
    }
    ruleSetsMapping.clear();
    for( SchemaMap::iterator it = schemaMapping.begin();
            it != schemaMapping.end();
            it++ )
    {
        assert_msg( it->second != NULL, "Trying to destroy a program with a null metadata." );
        delete it->second;
    }
    schemaMapping.clear();
    for( index_t i=0; i<factQueries.size(); i++ )
    {
        assert_msg( factQueries[i] != NULL, "Trying to destroy a program with a null (fact) query object." );
        delete factQueries[i];
    }
    for( index_t i=0; i<ruleQueries.size(); i++ )
    {
        assert_msg( ruleQueries[i] != NULL, "Trying to destroy a program with a null (rule) query object." );
        delete ruleQueries[i];
    }
    for( index_t i=0; i<facts.size(); i++ )
    {
        assert_msg( facts[i] != NULL, "Trying to destroy a program with a null fact." );
        delete facts[i];
    }
    for( index_t i=0; i<rules.size(); i++ )
    {
        assert_msg( rules[i] != NULL, "Trying to destroy a program with a null rule." );
        delete rules[i];
    }
}
    
DBTerm*
DBProgram::createIntegerConstant( 
    int val )
{
    return new DBTerm(val);
}

DBTerm*
DBProgram::createStringConstant( 
    const string& val )
{
    return new DBTerm(val);
}

DBTerm*
DBProgram::createStringConstant( 
    char* val )
{
    return new DBTerm(val);
}

DBTerm*
DBProgram::createVariable( 
    const string& name )
{
    return new DBTerm(0,name);
}

DBTerm*
DBProgram::createVariable( 
    char* name )
{
    return new DBTerm(0,name);
}

DBAtom*
DBProgram::createAtom( 
    const string& predName, 
    const vector< DBTerm* >& terms )
{
    pair< index_t, bool > res = addPredicate(predName,terms.size());
    return new DBAtom(*this,res.first,terms);
}

DBAtom*
DBProgram::createAtom( 
    char* predName, 
    const vector< DBTerm* >& terms )
{
    pair< index_t, bool > res = addPredicate(predName,terms.size());
    return new DBAtom(*this,res.first,terms);
}

DBAtom*
DBProgram::createNegatedAtom( 
    const string& predName, 
    const vector< DBTerm* >& terms )
{
    const char* negName = DBNamesItem(predName,terms.size()).getNegativeName();
    pair< index_t, bool > res = addPredicate(negName,terms.size());
    delete negName;
    return new DBAtom(*this,res.first,terms,true);
}

DBAtom*
DBProgram::createNegatedAtom( 
    char* predName, 
    const vector< DBTerm* >& terms )
{
    const char* negName = DBNamesItem(predName,terms.size()).getNegativeName();
    pair< index_t, bool > res = addPredicate(negName,terms.size());
    delete negName;
    return new DBAtom(*this,res.first,terms,true);
}

DBAtom*
DBProgram::createBuiltinAtom(
    DBTerm* leftOp, 
    const string& binOp, 
    DBTerm* rightOp )
{
    return new DBAtom(*this,leftOp,binOp,rightOp);
}

DBLiteral*
DBProgram::createLiteral(
    DBAtom* a, 
    bool naf )
{
    return new DBLiteral(a,naf);
}

DBAtom*
DBProgram::createAggregateAtom(
    DBTerm* lowerGuard,
    const string& lowerBinop,
    DBTerm* upperGuard, 
    const string& upperBinop, 
    const string& aggregateFunction, 
    const vector< DBAggregateElement* >& aggregateSet,
    const std::string& name )
{
    pair< index_t, bool > res = addPredicate(name,0);
    return new DBAtom(
            *this,
            res.first,
            lowerGuard,
            lowerBinop,
            upperGuard,
            upperBinop,
            aggregateFunction,
            aggregateSet);
}

DBAggregateElement*
DBProgram::createAggregateElement( 
    const vector< DBTerm* >& terms,
    const vector< DBLiteral* >& lits )
{
    return new DBAggregateElement(terms,lits);
}

DBRule*
DBProgram::createRule( 
    const vector< DBAtom* >& head,
    const vector< DBLiteral* >& body,
    bool hasNegation, 
    bool hasAggregates, 
    bool hasBuiltins )
{
    return new DBRule(head,body,hasNegation,hasAggregates,hasBuiltins);
}

void
DBProgram::createAndAddRule( 
    const vector< DBAtom* >& head,
    const std::vector< DBLiteral* >& body,
    bool hasNegation,
    bool hasAggregates,
    bool hasBuiltins )
{
    addRule(new DBRule(head,body,hasNegation,hasAggregates,hasBuiltins));
}

void
DBProgram::addRule(
    DBRule* r )
{
    // Rules are added to the program in a way such that
    // if a rule is stored in the rules vector at position "i",
    // its query object is stored at the same position of the 
    // query objects vector. 
    assert_msg( r != NULL, "Trying to add a null rule." );
    // Let r be the current rule and p_i be one of its head predicates,
    // add the index of r to the set of rules having p_i in the head.
    const std::vector< DBAtom* >& head = r->getHead();
    const std::vector< DBLiteral* >& body = r->getBody();
    // If it deals with a fact, add to facts.
    // Otherwise, add to rules.
    if( head.size() == 1 && body.size() == 0 )
    {
        assert_msg( head[0] != NULL, "Null head atom." );
        // Only standard atoms can be found in the head. 
        // Thus, this control is not necessary.
        assert_msg( !head[0]->isBuiltin(), "A builtin atom occurs in the head." );
        assert_msg( !head[0]->isAggregate(), "An aggregate atom occurs in the head." );
        facts.push_back(r);
    }
    else
    {
        for( unsigned i=0; i<head.size(); i++ )
        {
            const DBAtom* headAtom = head[i];
            assert_msg( headAtom != NULL, "Null head atom." );
            // Only standard atoms can be found in the head. 
            // Thus, this control is not necessary.
            assert_msg( !headAtom->isBuiltin(), "A builtin atom occurs in the head." );
            assert_msg( !headAtom->isAggregate(), "An aggregate atom occurs in the head." );
            
            // FIXME: if a rule is disjunctive it might be added to more than
            // one sub-program!!!
            addToPredicateRuleSet(headAtom->getPredIndex(),rules.size());
            // Add an edge to depgraph from each body literal to each head atom.
            for( unsigned j=0; j<body.size(); j++ )
            {
                assert_msg( body[j] != NULL, "Trying to create a rule with a null body literal." );
                // An head atom cannot be a builtin.
                addEdgeToDepGraph(body[j],headAtom->getPredIndex());
            } 
        }
        // Add rule r...
        rules.push_back(r);
    }
}

void
DBProgram::setQueryBuilder( 
    QueryBuilder* build )
{
    assert_msg( build != NULL, "Null query builder" );
    queryBuilder = build;
}

void
DBProgram::computeQueryObjects()
{
    assert_msg( isRuleRecursive.size() == rules.size(), 
            "Components' subprograms haven't been computed yet." ); 
    assert_msg( queryBuilder != NULL, "Null query builder" );
    
    // Iterate program rules/facts and generate their associated queries
    for( index_t i=0; i<facts.size(); i++ )
    {
        DBRule* fact = facts[i];
        assert_msg( fact != NULL, "Null fact" );
        // TODO
        //queryBuilder->rewriteFact();
        //factQueries.push_back(queryBuilder->getQueryObject());
    }
    for( index_t i=0; i<rules.size(); i++ )
    {
        DBRule* rule = rules[i];
        assert_msg( rule != NULL, "Null rule" );
        if( isRuleRecursive[i] )
            queryBuilder->rewriteRecursiveRule(rule);
        else
            queryBuilder->rewriteNonRecursiveRule(rule);
        
        ruleQueries.push_back(queryBuilder->getQueryObject());
    }
}

const std::vector< QueryObject* >&
DBProgram::getRuleQueryObjects() const
{
    return ruleQueries;
}

const std::vector< QueryObject* >&
DBProgram::getFactQueryObjects() const
{
    return factQueries;
}

const Metadata*
DBProgram::getMetadata(
    index_t predIndex ) const
{
    SchemaMap::const_iterator it = schemaMapping.find(predIndex);
    if( it != schemaMapping.end() )
        return it->second;
    else
        return NULL;
}

const DBRuleSet*
DBProgram::getPredicateRuleSet(
    index_t predIndex ) const
{
    RuleSetsMap::const_iterator it = ruleSetsMapping.find(predIndex);
    if( it != ruleSetsMapping.end() )
        return it->second;
    else
        return NULL;
}

pair< index_t, bool >
DBProgram::addPredicate(
    const string& predName,
    unsigned arity )
{
    assert_msg( arity > 0, "Propositional atoms are not allowed" );
    pair< index_t, bool > res = predicates.add(predName,arity);
    if( res.second )
    {
        // A new predicate..
        assert_msg( schemaMapping.find(res.first) == schemaMapping.end(), 
                "This predicate has not been added yet, but it has been already mapped" );
        // Retrieve the actual name of the table.
        string* actualTableName = getDBConnection().retrieveTableName(
                predicates.getItem(res.first).getPositiveName(),arity);
        assert_msg( actualTableName != NULL, "Invalid table name" );
                
        // Retrieve the attribute list of table "name".
        vector< string >* attributeNames = NULL;
        // If a predicate name is negative, just remind that the real name 
        // is the one starting after the first char ('-').
        attributeNames = getDBConnection().retrieveTableSchema(*actualTableName,arity);
        assert_msg( attributeNames != NULL, "Invalid attribute list" );
        assert_msg( attributeNames->size() == arity, "Invalid arity" );

        Metadata* data = new Metadata(res.first,actualTableName,attributeNames);
        schemaMapping[res.first] = data; 
    }
    return res;
}

void
DBProgram::computeStrictlyConnectedComponents()
{
    assert_msg( graph != NULL, "Null graph" );
    // Boost function "strong_components" computes the 
    // SCCs of a graph and returns them in a reverse 
    // topological order.
    graph->computeStronglyConnectedComponents();
}

void
DBProgram::computeComponentSubPrograms()
{
    assert_msg( graph != NULL, "Null graph" );
    assert_msg( componentSubPrograms.size() == 0, "It's to be allocated only here." );
    
    const Components& components = graph->getComponentList();
    // An element of this array is true iff an atom of the component with
    // the index of the field in the array occurs in the positive body of
    // the current rule. Only valid if the componentIndex is also contained
    // in componentsThatReceiveRule. And only then, the field
    // posBodyHasStdAtomOf[componentIndex] was initialized for this rule.
    bool* posBodyHasStdAtomOf = new bool[components.size()];
    index_t* componentsThatReceiveRule = new index_t[components.size()];
    unsigned nrRuleReceivers;
    // An element here is true if the component with the corresponding index
    // was already inserted into componentsThatReceiveRule.
    bool* doesComponentReceiveRule = new bool[components.size()];
    for( unsigned componentIdx = 0; componentIdx < components.size(); componentIdx++ )
    {
        componentSubPrograms.push_back(DBSubProgram< index_t >());
        doesComponentReceiveRule[componentIdx] = false;
    }

    for( index_t i=0; i<rules.size(); i++ )
    {
        DBRule* r = rules[i];
        assert_msg( r != NULL, "Null rule" );
        
        // Count the number of components that receive the rule.
        nrRuleReceivers = 0;

        for( unsigned j=0; j<r->getHead().size(); j++ )
        {
            DBAtom* headAtom = r->getHead().at(j);
            assert_msg( headAtom != NULL, "Null head atom" );
                    
            // The index of the component of the current head atom.
            unsigned compIndex = graph->getAtomComponent(headAtom->getPredIndex());

            // If an atom A appears in the head of the current rule R and it
            // belongs to a component, then that component "receives" rule R.
            // Store (only once) in componentsThatReceiveRule the index of the
            // component of the current head atom and increase the
            // counter nrRuleReceivers.
            if( !doesComponentReceiveRule[compIndex] )
            {
                componentsThatReceiveRule[nrRuleReceivers++] = compIndex;
                posBodyHasStdAtomOf[compIndex] = false;
                doesComponentReceiveRule[compIndex] = true;
            }
        }

        // Traverse the body and update the array posBodyHasStdAtomOf.
        // Set to true each element of the array whose index corresponds
        // to the component index of the current body atom.
        if( r->getBody().size() > 0 )
        {
            for( unsigned j=0; j<r->getBody().size(); j++ )
            {
                DBLiteral* bodyLiteral = r->getBody().at(j);
                assert_msg( bodyLiteral != NULL, "Null body literal" );
                DBAtom* bodyAtom = bodyLiteral->getAtom();
                assert_msg( bodyAtom != NULL, "Null body atom" );
                
                // This field is only valid if compIndex was added to
                // componentsThatReceiveRule.
                posBodyHasStdAtomOf[graph->getAtomComponent(bodyAtom->getPredIndex())] = true;
            }
        }
        bool isRecursive = false;
        // Examine all and only the components that receive the current rule
        // and decide if the rule is an exit rule or a recursive rule.
        for( index_t j=0; j<nrRuleReceivers; j++ )
        {
            // If the positive body contains one atom that belongs to a
            // component C of some of the head atoms then the rule has to be
            // added as recursive to component C. Otherwise, it has to be
            // added as exit rule.
            if( posBodyHasStdAtomOf[componentsThatReceiveRule[j]] )
            {
                componentSubPrograms[componentsThatReceiveRule[j]].addRecursive(i);
                isRecursive = true;
            }
            else
                componentSubPrograms[componentsThatReceiveRule[j]].addExit(i);

            doesComponentReceiveRule[componentsThatReceiveRule[j]] = false;
        }
        // FIXME: we've got no disjunctive rules, thus distinguishing between
        // recursive and non-recursive rules is easy because we can't find 
        // a rule in two different components (in such a case we could 
        // consider that rule as a recursive rule in one component and as a 
        // non-recursive rule in the other one).
        assert_msg( nrRuleReceivers <= 1, "We aren't handling disjunction at the moment." );
        isRuleRecursive.push_back(isRecursive);
    }
    delete[] posBodyHasStdAtomOf;
    delete[] componentsThatReceiveRule;
    delete[] doesComponentReceiveRule;
}

const std::vector< DBSubProgram< index_t > >&
DBProgram::getComponentSubPrograms() const
{
    assert_msg( componentSubPrograms.size() > 0, 
            "Component sub programs haven't been computed yet." );
    return componentSubPrograms;
}

bool
DBProgram::addToPredicateRuleSet(
    index_t predIndex,
    unsigned ruleIndex )
{
    RuleSetsMap::const_iterator it = ruleSetsMapping.find(predIndex);
    if( it == ruleSetsMapping.end() )
    {
        DBRuleSet* subP = new DBRuleSet();
        subP->insert(ruleIndex);
        ruleSetsMapping[predIndex] = subP;
        return true;
    }
    else
    {
        pair< DBRuleSet::const_iterator, bool > res = it->second->insert(ruleIndex);
        return res.second;
    }
}

void
DBProgram::addEdgeToDepGraph( 
    DBLiteral* source,
    index_t targetLabel )
{
    assert_msg( graph != NULL, "The graph has not been initialized." );
    assert_msg( source != NULL, "Trying to add an edge from a null literal." );
    DBAtom* sourceAtom = source->getAtom();
    assert_msg( sourceAtom != NULL, "Trying to add an edge from a null atom." );
    if( !sourceAtom->isBuiltin() )
    {
        index_t sourceLabel = sourceAtom->getPredIndex();
        if( sourceAtom->isAggregate() )
        {
            // First of all, add an edge from each literal 
            // in the aggregate set to the aggregate atom.
            for( unsigned i=0; i<sourceAtom->getAggregateElements().size(); i++ )
            {
                DBAggregateElement* sourceAggrElem = sourceAtom->getAggregateElements().at(i);
                assert_msg( sourceAggrElem != NULL, "Null element in an aggregate set." );
                for( unsigned j=0; j<sourceAggrElem->getLiterals().size(); j++ )
                {
                    DBLiteral* l = sourceAggrElem->getLiterals().at(j);
                    assert_msg( l != NULL, "Null literal in an aggregate set." );
                    // An aggregate atom cannot be true negated.
                    addEdgeToDepGraph(l,sourceLabel);
                }
            }
        }

        if( source->isNaf() )
            graph->addNegativeEdge(sourceLabel,targetLabel);
        else
            graph->addPositiveEdge(sourceLabel,targetLabel);
    }
}