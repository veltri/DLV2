input = """
p(1) :- #count{X:q(X)}=1.
q(X) :- p(X).
"""
output = """
DEPGRAPH: (3 atoms, 1 components) cyclic hcf stratified not_tight

0 --> 1
1 --> 2
2 --> 0


COMPONENT 0: cyclic hcf stratified
{ 0 1 2 }


Predicate names map:
0: p
2: #count{X:q}
1: q


"""
