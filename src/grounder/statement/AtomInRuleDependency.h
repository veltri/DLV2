//
// Created by davide on 28/05/15.
//

#ifndef DLV2_ATOMINRULEDEPENDENCY_H
#define DLV2_ATOMINRULEDEPENDENCY_H


#include "Rule.h"

using namespace std;


namespace DLV2{
namespace grounder {

class AtomInRuleDependency {
public:
    AtomInRuleDependency(Rule* rule):rule(rule){};
    void findPossibleBind();
    void findAtomDependencyBoundVariables();
    vector<unsigned> getBindAtom();
    //Return the size of the variables in boundVariables of the atom
    unsigned removeVariableInBoundVariables(unsigned atom,Term* variable,bool& removed);

 private:
    Rule *rule;
    unordered_map <unsigned int, set_term> boundVariables;
    const unordered_multimap <unsigned int, unordered_multimap<unsigned int, Term *>> atom_dependency;
    unordered_multimap<Term *, unsigned> possible_bind;
};


}
}

#endif //DLV2_ATOMINRULEDEPENDENCY_H
