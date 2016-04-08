/*
 * StatementDependency.cpp
 *
 *  Created on: 03/apr/2014
 *      Author: Davide
 */

#include "StatementDependency.h"

#include <algorithm>

#include <boost/graph/graph_utility.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/graph/topological_sort.hpp>
#include "../../util/Utils.h"

#include "../table/PredicateExtension.h"
#include "../statement/InputRewriter.h"
#include "../../input/InMemoryInputBuilder.h"
#include "RewriteMagic.h"
namespace DLV2{


namespace grounder{

StatementDependency* StatementDependency::statementDependency;


void StatementAtomMapping::addRule(Rule* r) {
	set_predicate head = r->getPredicateInHead();
	set_predicate body = r->getPredicateInBody();

	for (auto i : head) {
		headMap.insert( { i->getIndex(), r });
	}
	for (auto i : body) {
		bodyMap.insert( { i->getIndex(), r });
	}
}

void StatementAtomMapping::getRuleInHead(index_object p, vector<Rule*>& rules) {
	auto pair1 = headMap.equal_range(p);
	for (; pair1.first != pair1.second; ++pair1.first)
		rules.push_back(pair1.first->second);
}


bool StatementAtomMapping::isInHead(index_object p) {
	if (headMap.find(p) != headMap.end())
		return true;
	return false;
}

bool StatementAtomMapping::isInBody(index_object p) {
	if (bodyMap.find(p) != bodyMap.end())
		return true;
	return false;
}

StatementAtomMapping::~StatementAtomMapping() {}

/*
 *
 *
 *
 *
 * 	END StatementAtomMapping
 *
 *
 *
 *
 *
 */

void DependencyGraph::addInDependency(Rule* r) {
	// Temporary set of predicates
	unordered_set<index_object> head_predicateVisited;
	unordered_set<index_object> body_predicateVisited;



	for (auto head_it = r->getBeginHead(); head_it != r->getEndHead(); head_it++) {
		//Predicate* pred_head = (*head_it)->getPredicate();
		set_predicate predicates_head=(*head_it)->getPredicates();



		for(auto pred_head:predicates_head){

			// Check if the predicate in the head has been visited
			if ( !head_predicateVisited.count(pred_head->getIndex())) {

				// Set this predicate as visited
				head_predicateVisited.insert(pred_head->getIndex());

	//			// If the rule has no positive predicate in its body, is added a dummy edge in order to not lose this rule
	//			// when the components graph is created
	//			if(r->getPositivePredicateInBody().size()==0)
	//				addEdge(pred_head->getIndex(), pred_head->getIndex(),1);

				bool addPositiveEdge=false;

				for (auto body_it = r->getBeginBody(); body_it != r->getEndBody(); body_it++) {
					// Check if the predicate is positive, otherwise skip it
					if (!(*body_it)->isNegative()) {

						for(auto pred_body:(*body_it)->getPredicates()){
							// Check if the predicate in the head has been visited
							if(!body_predicateVisited.count(pred_body->getIndex())){
								body_predicateVisited.insert(pred_body->getIndex());
								addEdge(pred_body->getIndex(), pred_head->getIndex(),1);
								addPositiveEdge=true;
							}
						}

					}
					else{

						for(auto pred_body:(*body_it)->getPredicates()){
							// Check if the predicate in the head has been visited
							if(!body_predicateVisited.count(pred_body->getIndex())){
								body_predicateVisited.insert(pred_body->getIndex());
								if(!(*body_it)->isAggregateAtom())
									addEdge(pred_body->getIndex(), pred_head->getIndex(),-1);
								else{
									//TODO Add edge -1 with aggregate??????
									addEdge(pred_body->getIndex(), pred_head->getIndex(),1);
									addPositiveEdge=true;
								}
							}
						}

					}

				}

				// If the rule has no positive predicate in its body, is added a dummy edge in order to not lose this rule
				// when the components graph is created
				if(!addPositiveEdge)
					addEdge(pred_head->getIndex(), pred_head->getIndex(),1);
			}
			//Set all predicate in the body as unvisited, and then continue with the next atom
			body_predicateVisited.clear();
		}
	}

	//Add for each choice element the dependency with the atom in the right of :
	if(r->getSizeHead()>0){
		auto head_atom=r->getAtomInHead(0);
		if( head_atom->isChoice()){
			for(unsigned i=0;i<head_atom->getChoiceElementsSize();i++){
				for(auto pred_body:head_atom->getChoiceElement(i)->getPredicatePositiveInNaf()){
					addEdge(pred_body->getIndex(), head_atom->getChoiceElement(i)->getFirstAtom()->getPredicate()->getIndex(),1);
				}
			}
		}
	}

}

void DependencyGraph::deleteVertex(unordered_set<index_object>& delete_pred) {

	while (delete_pred.size() > 0) {
		// Boost actually re-indexes the vertices after one vertex has been deleted.
		// So it is needed to find again the new vertex index for each predicate.
		index_object current_pred = *delete_pred.begin();
		boost::graph_traits<Graph>::vertex_iterator vi, vi_end, next;
		tie(vi, vi_end) = boost::vertices(depGraph);
		for (next = vi; vi != vi_end; vi = next) {
			++next;
			if (current_pred == depGraph[*vi].pred_id) {
				remove_vertex(*vi, depGraph);
				break;
			}
		}
		delete_pred.erase(current_pred);
	}
}

void DependencyGraph::printFile(string fileGraph) {
	using namespace boost;

	typedef property_map<Graph, vertex_index_t>::type IndexMap;
//	IndexMap index = get(vertex_index, depGraph);
	IndexMap index = get(vertex_index, depGraph);
	graph_traits<Graph>::edge_iterator ei, ei_end;
	string graphDOT = "digraph Dependency_Graph{\n";

	// Print the edges
	for (tie(ei, ei_end) = edges(depGraph); ei != ei_end; ++ei) {
		index_object p1 = index[source(*ei, depGraph)];
		index_object p2 = index[target(*ei, depGraph)];
		graphDOT += lexical_cast<string>(p1) + "->" + lexical_cast<string>(p2) + ";\n";
	}

	//Print labels  (the name of the predicate)
	for (unsigned int i = 0; i < num_vertices(depGraph); i++) {
		graphDOT += lexical_cast<string>(i) + " [label= \"";
		string predicate =  PredicateExtTable::getInstance()->getPredicateExt(depGraph[i].pred_id)->getPredicate()->getName();
		graphDOT += predicate + "  " + "\"];\n";
	}
	graphDOT += "}\n";

	ofstream myfile;
	myfile.open(fileGraph);
	myfile << graphDOT;
	myfile.close();
	string COMMAND = "dot -Tsvg " + fileGraph + " -O";
	system(COMMAND.c_str());
	remove(fileGraph.c_str());

}

void DependencyGraph::print() {
	using namespace boost;

	typedef property_map<Graph, vertex_index_t>::type IndexMap;
	IndexMap index = get(vertex_index, depGraph);
	graph_traits<Graph>::edge_iterator ei, ei_end;

	// Print the edges
	for (tie(ei, ei_end) = edges(depGraph); ei != ei_end; ++ei) {
		index_object p1 = index[source(*ei, depGraph)];
		index_object p2 = index[target(*ei, depGraph)];
		cout << "("
				<< depGraph[p1].pred_id << ","
				<< depGraph[p2].pred_id << ")" << " ";
	}

}

void DependencyGraph::addEdge(index_object pred_body, index_object pred_head, int weight) {
	unsigned int index_i, index_j;
	auto it1 = predicateIndexGMap.find(pred_body);
	// Check if each predicate is already present in the graph
	// otherwise assign at to it a new id, for this purpose the map size is used
	if (it1 != predicateIndexGMap.end())
		index_i = it1->second;
	else {
		index_i = predicateIndexGMap.size();
		predicateIndexGMap.insert( { pred_body, index_i });
	}
	auto it2 = predicateIndexGMap.find(pred_head);
	if (it2 != predicateIndexGMap.end())
		index_j = it2->second;
	else {
		index_j = predicateIndexGMap.size();
		predicateIndexGMap.insert( { pred_head, index_j });
	}

	// If add an edge positive with the same predicate not add in stratified
	// because is only for component, to add rule with not positive atom in body
	if(!(index_i==index_j && weight>0)){
		boost::add_edge(index_i, index_j, weight, stratifiedGraph);
		stratifiedGraph[index_i].pred_id = pred_body;
		stratifiedGraph[index_j].pred_id = pred_head;
	}
	if(weight>0){
		boost::add_edge(index_i, index_j, depGraph);
		// Set the predicate in the vertex
		depGraph[index_i].pred_id = pred_body;
		depGraph[index_j].pred_id = pred_head;
	}
}

void DependencyGraph::calculateStrongComponent(unordered_map<index_object, unsigned int> &componentDepependency) {

	using namespace boost;
	typedef graph_traits<Graph>::vertex_descriptor Vertex;

	std::vector<int> component_indices(num_vertices(depGraph)), discover_time(num_vertices(depGraph));
	std::vector<default_color_type> color(num_vertices(depGraph));
	std::vector<Vertex> root(num_vertices(depGraph));
	strong_components(depGraph, make_iterator_property_map(component_indices.begin(), get(vertex_index, depGraph)),
							  root_map(make_iterator_property_map(root.begin(), get(vertex_index, depGraph))).
							  color_map(make_iterator_property_map(color.begin(), get(vertex_index, depGraph))).
							  discover_time_map(make_iterator_property_map(discover_time.begin(), get(vertex_index, depGraph))));

	for (unsigned int i = 0; i < component_indices.size(); i++)
		componentDepependency.insert( { depGraph[i].pred_id, component_indices[i] });


}


void DependencyGraph::calculateUnstratifiedPredicate(unordered_set<index_object>& predicateUnstratified){
	using namespace boost;

	//Calculate the cycle in stratifiedGraph and verify thath not exist recursion and negation, if exist
	// then all the predicate in that cycle are not stratified

	typedef graph_traits<WeightGraph>::vertex_descriptor VertexWeight;

	std::vector<int> component_indices_weight(num_vertices(stratifiedGraph)), discover_time_weight(num_vertices(stratifiedGraph));
	std::vector<default_color_type> color_weight(num_vertices(stratifiedGraph));
	std::vector<VertexWeight> root_weight(num_vertices(stratifiedGraph));
	strong_components(stratifiedGraph, make_iterator_property_map(component_indices_weight.begin(), get(vertex_index, stratifiedGraph)),
							  root_map(make_iterator_property_map(root_weight.begin(), get(vertex_index, stratifiedGraph))).
							  color_map(make_iterator_property_map(color_weight.begin(), get(vertex_index, stratifiedGraph))).
							  discover_time_map(make_iterator_property_map(discover_time_weight.begin(), get(vertex_index, stratifiedGraph))));

	typedef property_map<WeightGraph, vertex_index_t>::type IndexMap;
	property_map<WeightGraph, edge_weight_t>::type weightmap = get(edge_weight, stratifiedGraph);
	IndexMap index = get(vertex_index, depGraph);
	graph_traits<WeightGraph>::edge_iterator ei, ei_end;

	// check recursion in the same rule
	for (tie(ei, ei_end) = edges(stratifiedGraph); ei != ei_end; ++ei) {
		index_object p1 = stratifiedGraph[index[source(*ei, stratifiedGraph)]].pred_id;
		index_object p2 = stratifiedGraph[index[target(*ei, stratifiedGraph)]].pred_id;

		if(p1==p2 && weightmap[*ei]<0){
			predicateUnstratified.insert(p1);
			PredicateExtTable::getInstance()->getPredicateExt(p1)->getPredicate()->setSolved(false);
		}
	}

	std::unordered_set<unsigned int> component_processed;
	for (unsigned int i = 0; i < component_indices_weight.size(); i++){
//		cout<<IdsManager::getStringStrip(IdsManager::PREDICATE_ID_MANAGER,stratifiedGraph[i].pred_id)<<" "<<component_indices_weight[i]<<endl;
		bool next=false;
		if(!component_processed.count(component_indices_weight[i])){
					for (tie(ei, ei_end) = edges(stratifiedGraph); ei != ei_end && !next; ++ei) {
						index_object p1 = stratifiedGraph[index[source(*ei, stratifiedGraph)]].pred_id;
						index_object i2 = index[target(*ei, stratifiedGraph)];

						// If in this component not find a negative arc
						// search if exist a negative arc with an edge in this component
						if(stratifiedGraph[i].pred_id==p1 && component_indices_weight[i]==component_indices_weight[i2] && weightmap[*ei]<0){
							component_processed.insert(component_indices_weight[i]);
							for (unsigned int k = 0; k < component_indices_weight.size(); k++)
								if(component_indices_weight[k]==component_indices_weight[i]){
									predicateUnstratified.insert(stratifiedGraph[k].pred_id);
									PredicateExtTable::getInstance()->getPredicateExt(stratifiedGraph[k].pred_id)->getPredicate()->setSolved(false);
								}
							next=true;
						}
					}
		}
	}
//		for(auto stratPred:predicateUnstratified){
//			cout<<"UNDEF "<<stratPred<<endl;
//		}
}

/*
 *
 *
 *
 *
 * 	END DependencyGraph
 *
 *
 *
 *
 *
 */

void ComponentGraph::addEdge(index_object pred_body, index_object pred_head, int weight) {

	if (componentDependency[pred_body] != componentDependency[pred_head])
		boost::add_edge(componentDependency[pred_body], componentDependency[pred_head], weight, compGraph);
}

void ComponentGraph::createComponent(DependencyGraph &depGraph,
		StatementAtomMapping &statementAtomMapping) {
	depGraph.calculateStrongComponent(componentDependency);
	depGraph.calculateUnstratifiedPredicate(predicateUnstratified);


	// For each component create a vertex in a graph
	// because when adding a edge the vertex have to be created and if exist one component
	// with a body in a rule with all fact are not skipped

	unordered_set<unsigned int> component_insert;
	for (auto it : componentDependency)
		if(component_insert.insert(it.second).second)
			boost::add_vertex(compGraph);


	vector<Rule*> rules;
	for (auto it : componentDependency) {

		index_object pred_head = it.first;


		statementAtomMapping.getRuleInHead(pred_head, rules);

		for (Rule *r : rules) {

			for (auto body_it = r->getBeginBody(); body_it != r->getEndBody(); body_it++) {

				bool isPositive = !(*body_it)->isNegative();

				for(auto pred_body:(*body_it)->getPredicates()){
					index_object index_pred_body = pred_body->getIndex();
					// Check if the predicate appear in the head also
					if (statementAtomMapping.isInHead(index_pred_body)) {
						int weight = isPositive;
						if (!isPositive)
							weight = -1;
						// FIXME if put negative edge check if exist positive edge
						addEdge(index_pred_body, pred_head, weight);

					}
				}


			}

			if(r->getSizeHead()>0){
				auto head_atom=r->getAtomInHead(0);
				if( head_atom->isChoice()){
					for(unsigned i=0;i<head_atom->getChoiceElementsSize();i++){
						for(auto pred_body:head_atom->getChoiceElement(i)->getPredicatePositiveInNaf()){
							index_object index_pred_body = pred_body->getIndex();
							if (statementAtomMapping.isInHead(index_pred_body)) {
								addEdge(index_pred_body, pred_head, 1);

							}
						}
						for(auto pred_body:head_atom->getChoiceElement(i)->getPredicateNegativeInNaf()){
							index_object index_pred_body = pred_body->getIndex();
							if (statementAtomMapping.isInHead(index_pred_body)) {
								addEdge(index_pred_body, pred_head, -1);

							}
						}
					}
				}
			}

		}
		rules.clear();
	}

}

bool ComponentGraph::isPredicateNotStratified(index_object predicate){
	return predicateUnstratified.count(predicate);
}

void ComponentGraph::printFile(string fileGraph) {

	string graphDOT = "digraph Component_Graph {\n";

	using namespace boost;
	property_map<WeightGraph, edge_weight_t>::type weightmap = get(edge_weight, compGraph);
	typedef graph_traits<WeightGraph>::edge_iterator edge_iter;
	std::pair<edge_iter, edge_iter> ep;
	edge_iter ei, ei_end;
	typedef property_map<WeightGraph, vertex_index_t>::type IndexMap;
	IndexMap index = get(vertex_index, compGraph);

	// Print the edges
	for (tie(ei, ei_end) = edges(compGraph); ei != ei_end; ++ei) {
		graphDOT += lexical_cast<string>(index[source(*ei, compGraph)]) + "->"
				+ lexical_cast<string>(index[target(*ei, compGraph)]) + "[color= ";
		// negative RED , BLUE positive
		if (weightmap[*ei] > 0)
			graphDOT += "blue";
		else
			graphDOT += "red";
		graphDOT += "];\n";
	}

	//Print the labels (the predicates in the component)
	for (unsigned int i = 0; i < num_vertices(compGraph); i++) {
		graphDOT += lexical_cast<string>(i);
		graphDOT += " [label= \"";
		for (auto it : componentDependency)
			if (it.second == i) {
				string predicate =PredicateExtTable::getInstance()->getPredicateExt(it.first)->getPredicate()->getName();
				graphDOT += predicate + "  ";
			}
		graphDOT += "\"];\n";
	}

	graphDOT += "}\n";

	ofstream myfile;
	myfile.open(fileGraph);
	myfile << graphDOT;
	myfile.close();
	string COMMAND = "dot -Tsvg " + fileGraph + " -O";
	system(COMMAND.c_str());
	remove(fileGraph.c_str());

}

void ComponentGraph::print() {
	for (unsigned int i = 0; i < num_vertices(compGraph); i++) {
		cout << "{ ";
		bool first = false;
		for (auto it : componentDependency)
			if (it.second == i) {
				string predicate = boost::lexical_cast<string>( it.first);
				if (!first) {
					cout << predicate + " ";
					first = true;
				} else
					cout << ", " << predicate << " ";

			}
		cout << "} ";
	}
}
void ComponentGraph::computeAnOrdering(list<unsigned int>& componentsOrdering) {

	// If the component graph is not connected, then if there are some components any ordering is valid
	if(num_vertices(compGraph)>=0 && num_edges(compGraph)==0 && componentDependency.size()>0){
		unordered_set<unsigned int> components;
		for(auto pair:componentDependency)
			components.insert(pair.second);
		for(auto it:components)
			componentsOrdering.push_back(it);

		return;
	}

	// If the component graph is a-cyclic is suffices to compute a topological sort to get a valid components ordering
	try {
		topological_sort(compGraph, front_inserter(componentsOrdering));
	// Otherwise an not_a_dag exception is thrown, and it is computed an ordering taking into account that the graph is cyclic
	} catch (boost::not_a_dag const& e) {
		this->recursive_sort(componentsOrdering);
	}

}

void ComponentGraph::printTheOrderingOfComponent(list<unsigned int>& componentsOrdering){
	cout<<"ORDER:"<<endl;
	for(auto comp:componentsOrdering){
		cout<<"Component "<<comp<<" ";
		for(auto it:componentDependency)
			if(it.second==comp)
				cout<<it.first;
		cout<<endl;
	}
}

void ComponentGraph::recursive_sort(list<unsigned int>& componentsOrdering) {

	// Recursive method:
	// If exist a cycle detect the component of each cycle and for each cycle delete one
	// negative edge that connect two vertices of the same cycle, if topological sort don't report
	// error then exit else redo all the operation until all the cycle are deleted


	// Calculate the strong component (the cycle in the graph)
	using namespace boost;
	property_map<WeightGraph, edge_weight_t>::type weightmap = get(edge_weight, compGraph);
	typedef graph_traits<WeightGraph>::edge_iterator edge_iter;
	std::pair<edge_iter, edge_iter> ep;
	edge_iter ei, ei_end;
	vector<edge_iter> edgeToRemove;
	typedef property_map<WeightGraph, vertex_index_t>::type IndexMap;
	IndexMap index = get(vertex_index, compGraph);


	typedef graph_traits<WeightGraph>::vertex_descriptor VertexWeight;

	std::vector<int> component_indices_weight(num_vertices(compGraph)), discover_time_weight(num_vertices(compGraph));
	std::vector<default_color_type> color_weight(num_vertices(compGraph));
	std::vector<VertexWeight> root_weight(num_vertices(compGraph));
	strong_components(compGraph, make_iterator_property_map(component_indices_weight.begin(), get(vertex_index, compGraph)),
							  root_map(make_iterator_property_map(root_weight.begin(), get(vertex_index, compGraph))).
							  color_map(make_iterator_property_map(color_weight.begin(), get(vertex_index, compGraph))).
							  discover_time_map(make_iterator_property_map(discover_time_weight.begin(), get(vertex_index, compGraph))));

	// For each element of each component if find a negative edge that start with the element and finish with a vertex with the same
	// component then delete the edge and process another component
	std::unordered_set<unsigned int> componentProcessed;
	for(unsigned int i=0;i<component_indices_weight.size();i++){
		if(componentProcessed.count(component_indices_weight[i]))continue;
		for (tie(ei, ei_end) = edges(compGraph); ei != ei_end; ++ei) {
			if (weightmap[*ei] < 0 && index[source(*ei, compGraph)]==i
					&& component_indices_weight[index[source(*ei, compGraph)]]==component_indices_weight[i] && component_indices_weight[index[target(*ei, compGraph)]]==component_indices_weight[i]){

				edgeToRemove.push_back(ei);
				componentProcessed.insert(component_indices_weight[i]);
				break;
			}
		}
	}

	for(auto edge:edgeToRemove)
		remove_edge(*edge,compGraph);

	try{
		topological_sort(compGraph, front_inserter(componentsOrdering));
	} catch (boost::not_a_dag const& e) {
		componentsOrdering.clear();
		this->recursive_sort(componentsOrdering);
	}


}


void ComponentGraph::computeAllPossibleOrdering(vector<vector<unsigned int>>& componentsOrderings) {
	//TODO
}

/*
 *
 *
 *
 * END ComponentGraph
 *
 *
 *
 *
 *
 */

void StatementDependency::addRuleMapping(Rule* r) {
	unsigned index=constraints.size()+weak.size()+rules.size();
	r->setIndex(index);
	if(r->isAStrongConstraint()){
		constraints.push_back(r);
		statementAtomMapping.addRule(r);
	}else if(r->isWeakConstraint()){
		weak.push_back(r);
	}else{
		addAtomMappingAndSetEdb(r);
		rules.push_back(r);
	}
}

bool StatementDependency::magic() {
	string errmsg;
	unsigned queryConstraints = 0;
	HandleQuery(queryConstraints);
	if (query.empty()) {
		errmsg = "No query supplied.";
		return false;
	} else if (constraints.size() > queryConstraints) {
		errmsg = "The program contains integrity constraints.";
		return false;
	} else if (weak.size() > 0) {
		errmsg = "The program contains weak constraints.";
		return false;
	} else if (hasAggregate) {
		errmsg = "The program contains aggregates.";
		return false;
	} else if (Options::globalOptions()->getOptionFrontend() != FRONTEND_CAUTIOUS
	&& Options::globalOptions()->getOptionFrontend() != FRONTEND_BRAVE) {
		errmsg = "Neither brave nor cautious reasoning was specified.";
		return false;
	} else if (rules.empty()) {
		errmsg = "IDB is empty or has become empty due to optimizations.";
		return false;
	} else if(hasNegativeAtom)
		errmsg = "NO negative";

	if (errmsg.empty()) {

		bool isGroundQuery = true;
		for (auto atom : query)
			if (!atom->isGround()) {
				isGroundQuery = false;
				break;
			}
		RewriteMagic rewriteMagic(rules, constraints, weak, &query,
				isGroundQuery);
		rewriteMagic.rewrite(isGroundQuery);

		simplifyMagicRules();

		if(Options::globalOptions()->isPrintRewrittenProgram()){
			cerr<<"----------MAGIC PROGRAM----------"<<endl;
			for(auto r:rules){
				r->print(cerr);
			}
			for(auto r:constraints)
				r->print(cerr);

			cerr<<"----------    END      ----------"<<endl;
		}

	}
	return true;
}

void StatementDependency::simplifyMagicRules(){
	//Check if the magic rewriting create a fact rule
	for(unsigned i=0;i<rules.size();i++){
		Rule *rule=rules[i];
		if(rule->isAFact()){
			Atom *fact=rule->getAtomInHead(0);

			fact->setFact(true);
			Predicate* predicate = fact->getPredicate();
//			IndexingStructure* atomSearcher=nullptr;
//			PredicateExtTable::getInstance()->getPredicateExt(predicate)->getAtomSearcher(FACT);
//			if(Options::globalOptions()->getCheckFactDuplicate())
//				atomSearcher=instancesTable->getPredicateExt(predicate)->addAtomSearcher(FACT,HASHSET,nullptr);
//			if(atomSearcher==nullptr || atomSearcher->find(fact)==nullptr){
			PredicateExtTable::getInstance()->getPredicateExt(predicate)->addAtom(fact,FACT);
//				if (!Options::globalOptions()->isNofacts()) {
					OutputBuilder::getInstance()->onFact(fact);
//				}
			delete rule;
			rules.erase(rules.begin()+i);
		}
	}
	//Check duplicate rule
	for(unsigned i=0;i<rules.size();i++){

		for(unsigned j=i+1;j<rules.size();j++){

			if(*rules[i]==*rules[j]){
				rules[j]->free();
				delete rules[j];
				rules.erase(rules.begin()+j);
			}
		}

	}

}

void StatementDependency::addAtomMappingAndSetEdb(Rule *r){
	if(!r->isAStrongConstraint() && !r->isWeakConstraint()){
		set_predicate pred_head=r->getPredicateInHead();
		for(auto p:pred_head)p->setIdb();
	}
	statementAtomMapping.addRule(r);
}

void StatementDependency::createDependencyGraph(PredicateTable* pt) {

	bool appliedMagicRewriting=false;
	if(!query.empty()){
		appliedMagicRewriting=magic();

		if(appliedMagicRewriting){
			statementAtomMapping.clear();

			for(unsigned i=0;i<constraints.size();i++){
				constraints[i]->setIndex(rules.size()+i);
				addAtomMappingAndSetEdb(constraints[i]);
			}
		}
	}


	for(unsigned i=0;i<rules.size();i++){
		Rule * rule=rules[i];
		if(appliedMagicRewriting){
			addAtomMappingAndSetEdb(rule);
			rule->setIndex(i);
		}
		depGraph.addInDependency(rule);
	}
	unordered_set<index_object> delete_pred;
	pt->getEdbPredicate(delete_pred);
	depGraph.deleteVertex(delete_pred);

}

void StatementDependency::createComponentGraph() {
	compGraph.createComponent(depGraph, statementAtomMapping);
}

// An utility function that specifies how to sort the rules of a component
bool sortRules (Rule* r1,Rule* r2) {
	set_predicate headSecondRule=r2->getPredicateInHead();
	for(auto it=r1->getBeginBody();it!=r1->getEndBody();it++){
		Predicate* pred=(*it)->getPredicate();
		if(pred!=nullptr && headSecondRule.count(pred))
			return false;
	}
	return true;

}

void StatementDependency::createComponentGraphAndComputeAnOrdering(vector<vector<Rule*>>& exitRules, vector<vector<Rule*>>& recursiveRules,
		vector<unordered_set<index_object>>& componentPredicateInHead,vector<vector<Rule*>>& constraintRules,vector<Rule*>& remainedConstraint) {
	/// Create the component graph
	compGraph.createComponent(depGraph, statementAtomMapping);

	/// Compute a possible ordering among components
	list<unsigned int> ordering;
	compGraph.computeAnOrdering(ordering);

	/// Declaration of some temporary variables
	vector<Rule*> componentsRules;
	int i=0;

	unordered_map<index_object, unsigned int> components=compGraph.getComponent();
	unordered_set<unsigned> addedRules;

	//For each constraint put the IDB predicates that appear in the constraint.For each component delete the predicates of this component in
	//the predicates of constraints and if all predicate are deleted a constraint can be grounded in this component
	using set_int = unordered_set<index_object>;
	//List of constraint and a set of IDB predicates that appear in the constraint
	using list_rule_setInt = list<pair<Rule*,set_int>>;
	list_rule_setInt constraint_rule;

	for(unsigned j=0;j<constraints.size();j++){
		set_predicate predicates_in_rule=constraints[j]->getPredicateInBody();
		set_int predicate_in_constraint;
		for(auto p:predicates_in_rule)if(!p->isEdb())predicate_in_constraint.insert(p->getIndex());
		constraint_rule.push_back({constraints[j],predicate_in_constraint});
	}


	for(auto comp: ordering){
		exitRules.push_back(vector<Rule*>());
		recursiveRules.push_back(vector<Rule*>());
		componentPredicateInHead.push_back(unordered_set<index_object>());
		constraintRules.push_back(vector<Rule*>());
		for (auto pair: components)
			if(pair.second==comp){
				/// Get all the rules for the current component
				index_object predicate=pair.first;
				statementAtomMapping.getRuleInHead(predicate,componentsRules);
				/// For each rule classify it as exit or recursive
				for(Rule* r: componentsRules){
					if(addedRules.insert(r->getIndex()).second){
						if(checkIfExitRule(comp,r)){
							exitRules[i].push_back(r);
						}

						else{
							recursiveRules[i].push_back(r);
							for(auto p:r->getPredicateInHead()){
								if(componentPredicateInHead[i].insert(p->getIndex()).second){
									//If a predicate is recursive add delta and next delta tables
									PredicateExtTable::getInstance()->getPredicateExt(p->getIndex())->addTables(2);
								}
							}
						}
					}
				}
				componentsRules.clear();
				vector<list_rule_setInt::iterator> to_delete;
				for(auto it=constraint_rule.begin();it!=constraint_rule.end();it++){
					if(it->second.count(predicate))
						it->second.erase(predicate);
					if(it->second.size()==0){
						constraintRules[i].push_back(it->first);
						to_delete.push_back(it);
					}
				}
				for(auto it:to_delete)constraint_rule.erase(it);
			}
		i++;
	}

	for(unsigned int i=0;i<recursiveRules.size();i++){
		if(recursiveRules[i].size()>=2)
			stable_sort(recursiveRules[i].begin(),recursiveRules[i].end(),sortRules);
	}

	for(auto it=constraint_rule.begin();it!=constraint_rule.end();it++){
		remainedConstraint.push_back(it->first);
	}
}


bool StatementDependency::checkIfExitRule(unsigned int component, Rule* rule){
	unordered_set<index_object> positivePredicates=rule->getPositivePredicateIndexInBody();
	unordered_map<index_object, unsigned int> components=compGraph.getComponent();

	for (auto pair: components){
		if(pair.second==component && positivePredicates.count(pair.first))
			return false;
	}
	return true;
}

void StatementDependency::print() {
//	string fileDGraph = Config::getInstance()->getFileGraph() + "DG";
//	string fileCGraph = Config::getInstance()->getFileGraph() + "CG";
//
//	if (Config::getInstance()->isDependency()) {
//		if (strcmp(fileDGraph.c_str(), "DG") == 0)
//			depGraph.print();
//		else
//			depGraph.printFile(fileDGraph);
//	}
//	if (Config::getInstance()->isComponent()) {
//		if (strcmp(fileCGraph.c_str(), "C
//	G") == 0)
//			compGraph.print();
//		else
//			compGraph.printFile(fileCGraph);
//
//	}
//	if (Config::getInstance()->isPrintRules())
//		for (Rule*r : rules)
//			r->print();

}

StatementDependency* StatementDependency::getInstance(){
	if(statementDependency==nullptr)
		statementDependency = new StatementDependency;

	return statementDependency;
}


/** creates appropriate constraints for implementing queries efficiently
  * Note: Error messages are not terminated by newline, since it is expected
  *       that some other message (indicating how the program will proceed)
  *       is printed immediately afterwards.
  * @param queryConstraints the number of constraints introduced by this query
  * @return false if some error occurred
  */
 bool StatementDependency::HandleQuery(unsigned &queryConstraints)
     {
     if( query.empty() )
         {
         // No query has been specified, but one is required when brave
         // or cautious reasoning are requested.
    	 if( Options::globalOptions()->getOptionFrontend() == FRONTEND_BRAVE
             || Options::globalOptions()->getOptionFrontend() == FRONTEND_CAUTIOUS )
             {
             cerr << "No query supplied. Cannot continue." << endl;
             return false;
             }
         else
             return true;
         }

//        if( TraceLevel >= 1 )
//            cdebug << "Handling Query " << *Query << "?" << endl;

     set_term variables;

     // Make one pass through the query, checking whether it is ground
     // or not and looking for the maximum variable index.
     for( vector<Atom*>::const_iterator i=query.begin();
          i != query.end();
          i++ )
         {
         if( ! (*i)->isGround() )
             {
             isQueryGround=false;

             set_term vars=(*i)->getVariable();
             variables.insert(vars.begin(),vars.end());
//                for( vector<Term*>::const_iterator j=(*i)->getTerms().begin();
//                     j != (*i)->getTerms().end();
//                     j++ )
//                    if( (*j)->getType()==VARIABLE )
//                        maxVar=max(maxVar,j->getVar());
//                    else if( j->isComplex() )
//                        {
//                        set<TERM> vars;
//                        j->getComplexTerm().getComplexVars(vars);
//                        for( set<TERM>::const_iterator v = vars.begin();
//                             v != vars.end(); v++ )
//                            maxVar=max(maxVar,v->getVar());
//                        }
                }
         }


     if( Options::globalOptions()->getOptionFrontend() == FRONTEND_CAUTIOUS )
         {

         if( isQueryGround )
             {
             // We do cautious reasoning and have a ground query.

             // The query is treated as an internal constraint.
             // Example: a, not b ?
             //  becomes :- a, not b.
             //
             // If a model is computed, this means that this model did not
             // violate the constraint, i.e. at least one of the query's
             // literals is false in this model.  This model can be seen as
             // a witness that the query is not true in all possible models.
             //
             // If no model is computed, the query is cautiously true.

             // Create a constraint containing exactly the query
             // conjunction and mark it as internal.
         	Rule *c=new Rule;
         	c->setBody(query);
            constraints.push_back(c);
            queryConstraints++;

//             if( TraceLevel >= 1 )
//                 cdebug << "                " << c << endl;
             }
         }
     else
         {
         // We either do brave reasoning, or just have a query without
         // reasoning (possibly coming from a frontend).  For now, we
         // forbid the latter for non-ground queries.
         if( Options::globalOptions()->getOptionFrontend() != FRONTEND_BRAVE  &&  ! isQueryGround )
             {
             cerr << "Non-ground queries are only supported with brave and "
                     "cautious reasoning." << endl;
             return false;
             }

         // Each ground literal in the query is transformed into a constraint,
         // which we add to the program (marked as internal).
         // Example: a, not b? becomes :- not a.
         //                            :- b.
         for( vector<Atom*>::const_iterator i=query.begin();
              i != query.end();
              i++ )
             if( (*i)->isGround() )
                 {
                 Rule *c=new Rule;
                 Atom *newAtom=(*i)->clone();
                 newAtom->setNegative(!((*i)->isNegative()));
                 c->addInBody(newAtom);
                 constraints.push_back(c);
                 queryConstraints++;

//                 if( TraceLevel >= 1 )
//                     cdebug << "                " << c << endl;
                 }
         }

     // If the query is non-ground, we need to create a new "query rule" with
     // the query in the body, and initialize the interpretation that will
     // hold the union or intersection, respectively, of all models found.
     if( ! isQueryGround )
         {
//         TERMS t;
//         for(unsigned i=0; i <= maxVar; i++)
//             t.push_back( TERM(i) );

    	 Rule *newRule=new Rule;
//    	 for(auto q:query)
//    		 newRule->addInBody(q->clone());
    	 newRule->setBody(query);
    	 string name=PREDNAME_QUERY;
		Predicate *newPred=new Predicate(name,variables.size(),false);
		PredicateTable::getInstance()->insertPredicate(newPred);
		PredicateExtTable::getInstance()->addPredicateExt(newPred);
		vector<Term*> terms;
		for(auto t:variables)terms.push_back(t);
    	 newRule->addInHead(new ClassicalLiteral(newPred,terms,false,false));

//         DISJUNCTION head;
//         head.add( ATOM(PREDNAME_QUERY,&t,PREDICATE_NAMES::typeQuery) );
//         IDB.push_back( RULE(&head,Query) );

//         if( TraceLevel >= 1 )
//             cdebug << "Adding rule for non-ground query: "
//                    << IDB.back() << endl;
//         assert( IDB.back().isSafe() );
		 rules.push_back(newRule);
         }
     return true;
     }



}
}
