input = """
% As of 2000-06-18 this generates empty components in some DEPGRAPHs.

c :- not b.                                                                     
a :- c.                                                                         
b :- a.                                                                         
a :- true.                                                                      
"""
output = """
DEPGRAPH: (4 atoms, 2 components) cyclic hcf not_stratified not_tight

0 --> 2
1 --> 0
2 --> 1
3 --> 2


COMPONENT 0: cyclic hcf not_stratified
{ 0 1 2 }
COMPONENT 1: acyclic hcf stratified
{ 3 }


Predicate names map:
3: true
1: b
0: c
2: a


"""
