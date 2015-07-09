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
Q12(A) :- edge(A,B), Path1(B).
Q12(A)?
"""
output = """
#rewriting: 2
"""
