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
#include "../../util/ErrorMessage.h"

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
    // FIXME: Aggregate predicate names are stored along with standard predicates at the moment.
    pair< index_t, bool > res = predicates.add(name,0);
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
    // query object vector. 
    assert_msg( r != NULL, "Trying to add a null rule." );
    // Let r be the current rule and p_i be one of its head predicates,
    // add the index of r to the set of rules having p_i in the head.
    const std::vector< DBAtom* >& head = r->getHead();
    const std::vector< DBLiteral* >& body = r->getBody();

    // Check safety!!!
    try
    {
        assertIsRuleSafe(r);
    }
    catch( SafetyException& exc )
    {
        ErrorMessage::errorDuringParsing(exc.what());
    }
    
    // If it's a fact, add to facts.
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
    bool* posBodyHasStdAtomOfComp = new bool[components.size()];
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
            assert_msg( !headAtom->isBuiltin(),
                    "Builtins have no corrispetive entries in the dependency graph" );
            unsigned compIndex = graph->getAtomComponent(headAtom->getPredIndex());

            // If an atom A appears in the head of the current rule R and it
            // belongs to a component, then that component "receives" rule R.
            // Store (only once) in componentsThatReceiveRule the index of the
            // component of the current head atom and increase the
            // counter nrRuleReceivers.
            if( !doesComponentReceiveRule[compIndex] )
            {
                componentsThatReceiveRule[nrRuleReceivers++] = compIndex;
                posBodyHasStdAtomOfComp[compIndex] = false;
                doesComponentReceiveRule[compIndex] = true;
            }
        }

        // Traverse the body and update the array posBodyHasStdAtomOf.
        // Set to true each element of the array whose index corresponds
        // to the component index of the current body atom.
        for( unsigned j=0; j<r->getBody().size(); j++ )
        {
            DBLiteral* bodyLiteral = r->getBody().at(j);
            assert_msg( bodyLiteral != NULL, "Null body literal" );
            DBAtom* bodyAtom = bodyLiteral->getAtom();
            assert_msg( bodyAtom != NULL, "Null body atom" );

            // This field is only valid if compIndex was added to
            // componentsThatReceiveRule.
            if( !bodyAtom->isBuiltin() )
                posBodyHasStdAtomOfComp[graph->getAtomComponent(bodyAtom->getPredIndex())] = true;
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
            if( posBodyHasStdAtomOfComp[componentsThatReceiveRule[j]] )
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
        // non-recursive rule in another one).
        assert_msg( nrRuleReceivers <= 1, "We aren't handling disjunction at the moment." );
        isRuleRecursive.push_back(isRecursive);
    }
    delete[] posBodyHasStdAtomOfComp;
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
DBProgram::assertIsRuleSafe(
    DBRule* rule ) const
        throw (SafetyException)
{
    assert_msg( rule != NULL, "Null rule" );
    const vector< DBAtom* >& head = rule->getHead();
    const vector< DBLiteral* >& body = rule->getBody();

    // For all head elements...
    for( typename vector< DBAtom* >::const_iterator i=head.begin(); 
            i != head.end();
            i++ )
    {
        assert_msg( *i != NULL, "Null head atom" );
        const DBAtom& headAtom = **i; 
        const std::vector< DBTerm* >& headAtomParams = headAtom.getTerms();
        // ...and the terms they contain:
        for( typename vector< DBTerm* >::const_iterator i1=headAtomParams.begin();
                i1 != headAtomParams.end();
                i1++ )
        {
            assert_msg( *i1 != NULL, "Null head term" );
            const DBTerm& headTerm = **i1;
            if( headTerm.isVar() &&
                    ( body.size() == 0 || !saves(body,headTerm) ) )
                throw SafetyException(*rule);

            // FIXME: We don't have functions at the moment.
//            if( headTerm.isFunction()
//                && !headTerm.getFunctionTerm().isConstantTerm()
//                && ( body.size() == 0 || !safeFunctionalTerm(body,headTerm) ) )
//                return false;
        }
    }
    // Check body safety!
    if( body.size() > 0 && !checkConjunctionSafety(body) )
        throw SafetyException(*rule);
}

bool
DBProgram::checkConjunctionSafety(
    const vector< DBLiteral* >& conjunction ) const
{
    vector< DBLiteral* > safeBody;
    vector< DBLiteral* > toBeChecked;

    for( typename vector< DBLiteral* >::const_iterator j=conjunction.begin();
            j != conjunction.end();
            j++ )
    {
        DBLiteral* literal = *j;
        assert_msg( literal != NULL, "Null literal" );
        if ( !literal->safetyMustBeChecked() || literal->isPropositional() )
        {
            safeBody.push_back(literal);
        }
        else
        {
            toBeChecked.push_back(literal);
        }
    }
    return checkLiteralsSafety(safeBody,toBeChecked);
}

bool
DBProgram::checkLiteralsSafety(
    vector< DBLiteral* >& safeBody, 
    vector< DBLiteral* >& toBeChecked ) const
{
    bool newSafeLiteral = true;

    while( toBeChecked.size() != 0 && newSafeLiteral )
    {
        newSafeLiteral = false;
        for( typename vector< DBLiteral* >::iterator i=toBeChecked.begin();
                i != toBeChecked.end();
                i++ )
        {
            DBLiteral* literal = *i;
            assert_msg( literal != NULL, "Null literal" );
            DBAtom* atom = literal->getAtom();
            assert_msg( atom != NULL, "Null atom" );
            if( literal->isAggregate() )
            {
                // Check safety via a proper function
                if( safeAggregate(safeBody,*literal) )
                {
                    newSafeLiteral = true;
                    safeBody.push_back(literal);
                    toBeChecked.erase(i);
                    break;
                }
            }
            else if( literal->isBuiltin() )
            {
                if( safeBuiltin(safeBody,*literal) )
                {
                    newSafeLiteral = true;
                    safeBody.push_back(literal);
                    toBeChecked.erase(i);
                    break;
                }
            }
            else
            {
                assert_msg( !literal->isAggregate(), "This shouldn't be an aggregate" );
                int numTermsToCheck = atom->getTerms().size();
                    // FIXME: We don't have complex builtins at the moment.
//                    if( literal->isBuiltin() && literal->isOutputBuiltin() )
//                    {
//                        int k = literal->getBuiltinObject().getNeedToBeBound();
//                        if ( k < 0 )
//                        {
//                            // All arguments but the last k need to be bound
//                            assert( (numTermsToCheck+k) >= 0 );
//                            numTermsToCheck = numTermsToCheck+k;
//                        }
//                        else
//                            // First k arguments need to be bound
//                            numTermsToCheck = k;
//                    }
                if( safeRegularAtom(safeBody,atom->getTerms(),numTermsToCheck) )
                {
                    newSafeLiteral = true;
                    safeBody.push_back(literal);
                    toBeChecked.erase(i);
                    break;
                }
            }
        }
    }
    return !toBeChecked.size();
}

bool
DBProgram::safeRegularAtom(
    const vector< DBLiteral* >& conjunction,
    const vector< DBTerm* >& params,
    const unsigned numTermsToCheck ) const
{
    unsigned count = 0;
    for( typename vector< DBTerm* >::const_iterator i=params.begin();
         i != params.end() && count < numTermsToCheck;
         i++, count++ )
    {
        DBTerm* term = *i;
        assert_msg( term != NULL, "Null term" );
        if( term->isVar() && !saves(conjunction,*term) )
            return false;
        // FIXME: We don't have functions at the moment.
//        if( (*i).isFunction() && !safeFunctionalTerm(conjunction,*i) )
//            return false;
    }
    return true;
}

bool
DBProgram::safeAggregate(
    const vector< DBLiteral* >& conjunction,
    const DBLiteral& aggrLit ) const
{
    DBAtom* aggrAtom = aggrLit.getAtom();
    assert_msg( aggrAtom != NULL, "Null atom" );
    assert_msg( aggrAtom->isAggregate(), "Not a valid aggregate" );
    
    // If aggrAtom is an assignment aggregate, its guard are safe!
    if( !aggrAtom->isAssignmentAggregate() )
    {
        // Otherwise, check safety of both lower guard...
        if( aggrAtom->getAggregateLowerGuard() != NULL &&
                aggrAtom->getAggregateLowerGuard()->isVar() &&
                !saves(conjunction,*aggrAtom->getAggregateLowerGuard()) )
                    return false;
    
        // ...and upper guard.
        else if( aggrAtom->getAggregateUpperGuard() != NULL &&
                aggrAtom->getAggregateUpperGuard()->isVar() &&
                !saves(conjunction,*aggrAtom->getAggregateUpperGuard()) )
                    return false;
    }
//    // Aggregates with ground sets and safe guards are safe.
//    if( agg_lit.getAggregate().hasGroundSet() )
//        return true;

    // Check safety of aggregate Conjunction.
    for( unsigned i=0; i<aggrAtom->getAggregateElements().size(); i++ )
    {
        // First of all, check safety of the current free vars.
        DBAggregateElement* element = aggrAtom->getAggregateElements().at(i);
        assert_msg( element != NULL, "Null aggregate element" );
        for( unsigned j=0; j<element->getTerms().size(); j++ )
        {
            DBTerm* term = element->getTerms().at(j);
            assert_msg( term != NULL, "Null aggregate element term" );
            if( term->isVar() && !saves(element->getLiterals(),*term) )
                return false;
        }
        // Then, check safety of the current conjunction.
        for( unsigned j=0; j<element->getLiterals().size(); j++ )
        {
            DBLiteral* literal = element->getLiterals().at(j);
            assert_msg( literal != NULL, "Null aggregate element literal" );
            // For all negative literals, builtins,...
            if( literal->safetyMustBeChecked() )
            {
                DBAtom* atom = literal->getAtom();
                assert_msg( atom != NULL, "Null aggregate element atom" );
                if( literal->isRegularAtom() )
                {
                    for( unsigned k=0; k<atom->getTerms().size(); k++ )
                    {
                        // If the current term is a variable, check whether it appears either in
                        // a positive literal of conjunction, or in a positive literal
                        // of the current element conjunction.
                        DBTerm* term = atom->getTerms().at(k);
                        assert_msg( term != NULL, "Null aggregate element term" );
                        if( term->isVar() && !saves(conjunction,*term)
                                && !saves(element->getLiterals(),*term) )
                            return false;

                        // FIXME: We don't have functions at the moment.
//                      if( (*par).isFunction()
//                                && !safeFunctionalTerm(conjunction,*par)
//                                && !safeFunctionalTerm(agg_lit.getAggregate().
//                                        getConjunction(),*par ) )
//                            return false;
                    }
                }
                else if( literal->isBuiltin() )
                {
                    if( !safeBuiltin(conjunction,*literal) &&
                            !safeBuiltin(element->getLiterals(),*literal) )
                        return false;
                }
                else // Literal is an aggregate
                {
                    assert_msg( 0, "Nested aggregates are not allowed" );
                }
            }
        }
    }
    return true;
}

bool
DBProgram::safeBuiltin(
    const vector< DBLiteral* >& conjunction,
    const DBLiteral& builtinLit ) const
{
    assert_msg( builtinLit.isBuiltin(), "Not a valid builtin" );
    DBAtom* builtinAtom = builtinLit.getAtom();
    assert_msg( builtinAtom != NULL, "Null atom" );
    DBTerm* leftOp = builtinAtom->getLeftOperand();
    assert_msg( leftOp != NULL, "Null left operand" );
    DBTerm* rightOp = builtinAtom->getRightOperand();
    assert_msg( rightOp != NULL, "Null left operand" );

    if( leftOp->isVar() && !saves(conjunction,*leftOp) )
        return false;
    if( rightOp->isVar() && !saves(conjunction,*rightOp) )
        return false;
    return true;
}

bool
DBProgram::saves(
    const vector< DBLiteral* >& conjunction,
    const DBTerm& term ) const
{
    if( term.isUnknownVar() )
        return false;

    bool saved=false;

    for( typename vector< DBLiteral* >::const_iterator j=conjunction.begin();
            !saved && j != conjunction.end();
            j++ )
    {
        DBLiteral* literal = *j;
        assert_msg( literal != NULL, "Null literal" );
        DBAtom* atom = literal->getAtom();
        assert_msg( atom != NULL, "Null atom" );
        if( literal->isSaviour() )
        {
            if( literal->isAggregate() )
            {
                assert_msg( literal->isAssignmentAggregate(),
                        "This isn't an assignment aggregate" );
                saved = *(atom->getAggregateLowerGuard()) == term;
            }
            else
            {
                const vector< DBTerm* >& terms = atom->getTerms();
                for( typename vector< DBTerm* >::const_iterator j1=terms.begin();
                        !saved && j1 != terms.end();
                        j1++ )
                {
                    DBTerm* bodyTerm = *j1;
                    assert_msg( bodyTerm != NULL, "Null term" );
                    if( bodyTerm->isVar() && *bodyTerm == term )
                        saved=true;
                }
            }
        }
        else if( literal->isBuiltin() )
        {
            if( atom->isEqualityBuiltin() )
            {
                DBTerm* t1 = atom->getRightOperand();
                DBTerm* t2 = atom->getLeftOperand();
                assert_msg( t1 != NULL, "Null term" );
                assert_msg( t2 != NULL, "Null term" );
                
                // Handle the case t = integer\constant.
                if( *t1 == term )
                    saved = ( t2->isConst() || t2->isInt() );

                // Handle the case integer\constant = t.
                if( *t2 == term )
                    saved = ( t1->isConst() || t1->isInt() );
            }
            // FIXME: We don't have complex builtins at the moment.
//            else if( literal.isOutputBuiltin() )
//            {
//                saved = literal.isBuiltinOutputVar(term);
//            }
        }
    }
    return saved;
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
