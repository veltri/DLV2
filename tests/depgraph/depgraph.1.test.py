input = """
% run with option -- depgraph
% component of b must be HCF

a(1) | -a(1).
b(X) | b(X) :-  a(X).

"""
output = """
DEPGRAPH: (3 atoms, 3 components) acyclic hcf stratified tight

0 --> 2
1 -->
2 -->


COMPONENT 0: acyclic hcf stratified
{ 2 }
COMPONENT 1: acyclic hcf stratified
{ 0 }
COMPONENT 2: acyclic hcf stratified
{ 1 }


Predicate names map:
1: -a
2: b
0: a


"""
