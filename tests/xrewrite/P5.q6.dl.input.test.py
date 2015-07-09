input = """
% Total TBox Axioms: 10

aux_0(X,Y) :- Path5(X).
aux_1(X,Y) :- Path3(X).
aux_2(X,Y) :- Path4(X).
aux_3(X,Y) :- Path2(X).
edge(X, Y) :- Path1(X).
edge(X,Y) :- aux_1(X,Y).
Path2(Y) :- aux_1(X,Y).
edge(X,Y) :- aux_2(X,Y).
Path3(Y) :- aux_2(X,Y).
edge(X,Y) :- aux_0(X,Y).
Path4(Y) :- aux_0(X,Y).
edge(X,Y) :- aux_3(X,Y).
Path1(Y) :- aux_3(X,Y).
Q6(A) :- edge(A,B), Path3(B).
Q6(A)?
"""
output = """
#rewriting: 2
"""
