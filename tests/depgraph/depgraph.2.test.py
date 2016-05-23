input = """
% run with option --depgraph
% the component of a must be cyclic

b(1).
a(X, Y) :- a(X, X), b(Y).

"""
output = """
DEPGRAPH: (2 atoms, 2 components) cyclic hcf stratified not_tight

0 --> 1
1 --> 1


COMPONENT 0: cyclic hcf stratified
{ 1 }
COMPONENT 1: acyclic hcf stratified
{ 0 }


Predicate names map:
0: b
1: a


"""
