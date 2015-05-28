//
// Created by davide on 28/05/15.
//

#include "AtomInRuleDependency.h"

void DLV2::grounder::AtomInRuleDependency::findPossibleBind() {
    //Avoid multiple costruction
    if(possible_bind.size()>0)return;

        int atom_counter=0;
        //First add all variable in positive atom
        for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();++atom,++atom_counter){
            Atom* current_atom=*atom;
            if(!(current_atom->isBuiltIn() || current_atom->isNegative() || current_atom->getAggregateElementsSize()>0)) {

                for (Term *variable:current_atom->getVariable())
                    possible_bind.insert({variable, atom_counter});
            }

        }

        //Second find the not cyclic assignments in built-in and aggregate atoms
        atom_counter=0;
        unordered_set<unsigned> cyclic_assignment;
        vector<unsigned> aggregates_positions;
        for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();++atom,++atom_counter){
            Atom *current_atom = *atom;

            if (current_atom->isBuiltIn() && current_atom->getBinop() == Binop::EQUAL) {
                //If one term is ground or is in possible_bind
                Term *firstGuard = current_atom->getTerm(0);
                Term *secondGuard = current_atom->getTerm(1);


                if ( ( firstGuard->isGround() && !secondGuard->isGround() ) ||
                     (possible_bind.count(firstGuard) && ! possible_bind.count(secondGuard))) {

                    possible_bind.insert({secondGuard,atom_counter});
                    current_atom->setAssignment(true);
                }else if ( ( !firstGuard->isGround() && secondGuard->isGround() ) ||
                           (possible_bind.count(secondGuard) && ! possible_bind.count(firstGuard))) {

                    possible_bind.insert({firstGuard,atom_counter});
                    current_atom->setAssignment(true);

                }//Cyclic dependency
                else if(!possible_bind.count(secondGuard) && ! possible_bind.count(firstGuard))
                    cyclic_assignment.insert(atom_counter);
            }//The aggregate assignment must be at the second
            else if(current_atom->getAggregateElementsSize()>0 && current_atom->getFirstBinop()==Binop::EQUAL){
                //If the guard is not in possible_bind
                if(!possible_bind.count(current_atom->getFirstGuard())){

                    possible_bind.insert({current_atom->getFirstGuard(),atom_counter});
                    current_atom->setAssignment(true);
                    aggregates_positions.push_back(atom_counter);
                }
            }


        }

        //For cyclic dependencies, try to find the order of evaluation of cyclic built-in and remove
        // at each iteration one built-in until cyclic_assignment is empty
        while(cyclic_assignment.size()>0){
            unordered_set<unsigned> deleted_builtin;
            for(auto cyclic_builtin:cyclic_assignment){
                Atom *current_atom = rule->getAtomInBody(cyclic_builtin);
                Term *firstGuard = current_atom->getTerm(0);
                Term *secondGuard = current_atom->getTerm(1);
                Term *bind_guard=nullptr;
                if ( possible_bind.count(firstGuard) && ! possible_bind.count(secondGuard))
                    bind_guard=secondGuard;
                else if ( possible_bind.count(secondGuard) && ! possible_bind.count(firstGuard))
                    bind_guard=firstGuard;
                if(bind_guard!=nullptr){
                    possible_bind.insert({bind_guard,cyclic_builtin});
                    current_atom->setAssignment(true);
                    deleted_builtin.insert(cyclic_builtin);
                }
            }
            //If no un-cyclic built-in is find stop
            if(deleted_builtin.size()==0)assert("Cyclic dependecy between built-in");
            for(auto element:deleted_builtin){cyclic_assignment.erase(element);}
        }

        //If an assignment aggregate have the guard in some built-in the aggregate is not an assignment
        for(auto aggregate_position:aggregates_positions){
            auto range_term_atom=possible_bind.equal_range(rule->getAtomInBody(aggregate_position)->getFirstGuard());
            for(auto it=range_term_atom.first;it!=range_term_atom.second;++it){
                if(!rule->getAtomInBody(it->second)->getAggregateElementsSize()>0){
                    rule->getAtomInBody(aggregate_position)->setAssignment(false);
                    break;
                }

            }
        }

}

void DLV2::grounder::AtomInRuleDependency::findAtomDependencyBoundVariables() {

    //Avoid multiple costruction
    if(atom_dependency.size()>0)return;
    unsigned atom_counter=0;
    for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();++atom,++atom_counter){
        Atom *current_atom = *atom;
        if(current_atom->isNegative() ||
           current_atom->isBuiltIn() ||
           current_atom->getAggregateElementsSize()>0){

            for(auto variable:current_atom->getVariable()){
                // For each variable that depends by positive or assignment atoms find
                // the atoms position of positive or assignment atoms that contains this variable
                // and put in atom_dependency the dependency between the  positive or assignment atoms and
                // the negative,built-in or aggregate atoms with the variable that share
                auto find_it=possible_bind.equal_range(variable);
                bool insert=find_it.first!=possible_bind.end();
                for(auto it=find_it.first;it!=find_it.second;++it){
                    unsigned atom_bind=it->second;
                    if(atom_bind==atom_counter){insert=false;continue;}
                    auto find_atom_bind=atom_dependency.find(atom_bind);
                    if(find_atom_bind!=atom_dependency.end()){
                        (*find_atom_bind).second.insert({atom_counter,variable});
                    }else{
                        unordered_multimap<unsigned,Term*> atomDependencyBind;
                        atomDependencyBind.insert({atom_counter,variable});
                        atom_dependency.insert({atom_bind, atomDependencyBind});
                    }
                }
                if(insert){
                    auto bound_find_it=boundVariables.find(atom_counter);
                    if(bound_find_it!=boundVariables.end())
                        (*bound_find_it).second.insert(variable);
                    else{
                        set_term terms;
                        terms.insert(variable);
                        boundVariables.insert({atom_counter,terms});
                    }
                }
            }

        }
    }


}
