input = """
f(1). f(2).

h(X) :- f(X).

a | b.

:- a, not 1 < #count{Z:f(Z)}.
"""
output = """
DEPGRAPH: (5 atoms, 5 components) acyclic hcf stratified tight

0 --> 1 4
1 -->
2 -->
3 -->
4 -->


COMPONENT 0: acyclic hcf stratified
{ 1 }
COMPONENT 1: acyclic hcf stratified
{ 4 }
COMPONENT 2: acyclic hcf stratified
{ 0 }
COMPONENT 3: acyclic hcf stratified
{ 2 }
COMPONENT 4: acyclic hcf stratified
{ 3 }


Predicate names map:
1: h
0: f
3: b
2: a
4: #count{Z:f}


"""
