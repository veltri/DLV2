input = """
var(m,c).
var(m,p).
var(m,a1).
var(w,e).
var(w,p).
var(w,a).
var(r,e).
var(r,c).
k_vertex("m",m).
k_vertex("w",w).
k_vertex("r",r).
k_vertex("m_w",m).
k_vertex("m_w",w).
k_vertex("m_r",m).
k_vertex("m_r",r).
k_vertex("w_r",w).
k_vertex("w_r",r).


% ***  Computes in the predicate hypertree(Father,Son)       ***
% ***  a k-width hypertree decomposition of a given query Q  ***
% ***  encoded by the base relation var(Atom,Variable).      ***
% ***  We assume distinct atoms have different names.        ***

k_decomposable(R,P):- component(P,R), trivial_component(P,R).

k_decomposable(R,P):- not trivial_component(P,R), good_vertex(S,R,P).
                      

good_vertex(S,R,P):- meets_conditions(S,R,P), not undecomposable(S,R,P).

undecomposable(S,R,P):- component(Q,S), subset(Q,S,P,R), 
                                              not k_decomposable(S,Q).
  


% *** Nondeterministic choice of any hypertree-decomposition of Q ***

hypertree(Father,Child):- parent(Father,_,Child). 

parent(root,query,V):- good_vertex(V,root,query), not diff_choice(root,query,V). 

parent(S,Q,V):- parent(R,P,S), good_vertex(V,S,Q), not diff_choice(S,Q,V), 
                  component(Q,S), subset(Q,S,P,R). 
parent(S,Q,Q):- parent(R,P,S), trivial_component(Q,S), subset(Q,S,P,R).

diff_choice(S,Q,V):- parent(S,Q,V1), is_k_vertex(V), V != V1.


% --------------------------------------------------------------------- 
% BUILT-IN (THE PROGRAM BELOW IS STRATIFIED)

component(P,R):- atom(P), is_k_vertex(R), 
                 not k_vertex(R,P), not non_var_subset(P,R).
component(P,R):- not non_first(P,R), atom(P), 
                      not k_vertex(R,P), is_k_vertex(R).
component(query,root):- true.

non_first(P,R):- path(Q,P,R), Q < P.
non_var_subset(P,R):- var(P,X), k_vertex(R,_), not var_k(R,X).

subset(P,R,Q,S):- component(P,R), component(Q,S), not non_subset(P,R,Q,S).
non_subset(P,R,Q,S):- belongs(A,P,R), component(Q,S), not belongs(A,Q,S).


% less_lex(Q,P):- var(Q,_), var(P,_), Q < P.

belongs(Q,P,S):- component(P,S), path(Q,P,S).
belongs(P,P,S):- component(P,S).
belongs(Q,query,root):- atom(Q).

path(Q,P,S):- adjac(Q,P,S).
path(Q,P,S):- adjac(Q,A,S), path(A,P,S).

adjac(Q,P,S):- atom(P), atom(Q), var(Q,X), var(P,X), 
                                 k_vertex(S,_), not var_k(S,X).

var_k(S,X):- k_vertex(S,P), var(P,X).

trivial_component(P,R):- component(P,R), not nontrivial_component(P,R).
nontrivial_component(P,R):- belongs(Q,P,R), Q != P.


% *** The following condition cuts off some redundant decompositions ***
meets_conditions(S,R,P):- k_vertex(S,_), k_vertex(R,Q),component(P,R), var_k(S,X), 
                           not var_k(R,X), not k_vertex(S,Q), not violate(S,R,P).

% *** Non optimized version of meets_conditions(S,R,P)  ***
% meets_conditions(S,R,P):- k_vertex(S,_), component(P,R), var_k(S,X), 
%                            not var_k(R,X), not violate(S,R,P).

meets_conditions(R,root,query):- k_vertex(R,_).

violate(S,R,P):- var_k(S,X), component(P,R), not var_c(P,R,X), not var_k(R,X).
violate(S,R,P):- var_c(P,R,X), var_k(R,X), k_vertex(S,_), not var_k(S,X).


var_c(P,R,X):- component(P,R), belongs(Q,P,R), var(Q,X).

is_k_vertex(S):- k_vertex(S,_).

atom(P):- var(P,X).

true.

% *** The question is ***
k_decomposable(root,query) ?
"""
output = """
var(m,c).
var(m,p).
var(m,a1).
var(w,e).
var(w,p).
var(w,a).
var(r,e).
var(r,c).
k_vertex("m",m).
k_vertex("w",w).
k_vertex("r",r).
k_vertex("m_w",m).
k_vertex("m_w",w).
k_vertex("m_r",m).
k_vertex("m_r",r).
k_vertex("w_r",w).
k_vertex("w_r",r).


% ***  Computes in the predicate hypertree(Father,Son)       ***
% ***  a k-width hypertree decomposition of a given query Q  ***
% ***  encoded by the base relation var(Atom,Variable).      ***
% ***  We assume distinct atoms have different names.        ***

k_decomposable(R,P):- component(P,R), trivial_component(P,R).

k_decomposable(R,P):- not trivial_component(P,R), good_vertex(S,R,P).
                      

good_vertex(S,R,P):- meets_conditions(S,R,P), not undecomposable(S,R,P).

undecomposable(S,R,P):- component(Q,S), subset(Q,S,P,R), 
                                              not k_decomposable(S,Q).
  


% *** Nondeterministic choice of any hypertree-decomposition of Q ***

hypertree(Father,Child):- parent(Father,_,Child). 

parent(root,query,V):- good_vertex(V,root,query), not diff_choice(root,query,V). 

parent(S,Q,V):- parent(R,P,S), good_vertex(V,S,Q), not diff_choice(S,Q,V), 
                  component(Q,S), subset(Q,S,P,R). 
parent(S,Q,Q):- parent(R,P,S), trivial_component(Q,S), subset(Q,S,P,R).

diff_choice(S,Q,V):- parent(S,Q,V1), is_k_vertex(V), V != V1.


% --------------------------------------------------------------------- 
% BUILT-IN (THE PROGRAM BELOW IS STRATIFIED)

component(P,R):- atom(P), is_k_vertex(R), 
                 not k_vertex(R,P), not non_var_subset(P,R).
component(P,R):- not non_first(P,R), atom(P), 
                      not k_vertex(R,P), is_k_vertex(R).
component(query,root):- true.

non_first(P,R):- path(Q,P,R), Q < P.
non_var_subset(P,R):- var(P,X), k_vertex(R,_), not var_k(R,X).

subset(P,R,Q,S):- component(P,R), component(Q,S), not non_subset(P,R,Q,S).
non_subset(P,R,Q,S):- belongs(A,P,R), component(Q,S), not belongs(A,Q,S).


% less_lex(Q,P):- var(Q,_), var(P,_), Q < P.

belongs(Q,P,S):- component(P,S), path(Q,P,S).
belongs(P,P,S):- component(P,S).
belongs(Q,query,root):- atom(Q).

path(Q,P,S):- adjac(Q,P,S).
path(Q,P,S):- adjac(Q,A,S), path(A,P,S).

adjac(Q,P,S):- atom(P), atom(Q), var(Q,X), var(P,X), 
                                 k_vertex(S,_), not var_k(S,X).

var_k(S,X):- k_vertex(S,P), var(P,X).

trivial_component(P,R):- component(P,R), not nontrivial_component(P,R).
nontrivial_component(P,R):- belongs(Q,P,R), Q != P.


% *** The following condition cuts off some redundant decompositions ***
meets_conditions(S,R,P):- k_vertex(S,_), k_vertex(R,Q),component(P,R), var_k(S,X), 
                           not var_k(R,X), not k_vertex(S,Q), not violate(S,R,P).

% *** Non optimized version of meets_conditions(S,R,P)  ***
% meets_conditions(S,R,P):- k_vertex(S,_), component(P,R), var_k(S,X), 
%                            not var_k(R,X), not violate(S,R,P).

meets_conditions(R,root,query):- k_vertex(R,_).

violate(S,R,P):- var_k(S,X), component(P,R), not var_c(P,R,X), not var_k(R,X).
violate(S,R,P):- var_c(P,R,X), var_k(R,X), k_vertex(S,_), not var_k(S,X).


var_c(P,R,X):- component(P,R), belongs(Q,P,R), var(Q,X).

is_k_vertex(S):- k_vertex(S,_).

atom(P):- var(P,X).

true.

% *** The question is ***
k_decomposable(root,query) ?
"""
