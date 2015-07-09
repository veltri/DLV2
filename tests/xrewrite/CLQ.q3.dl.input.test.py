input = """
% Expressiveness: Sticky %

% Schema %

% Sp(X) special node.
% E(X,Y) edge from X to Y.
% C2(X,Y) clique of size 2.
% C3(X,Y,,Z) clique of size 3.
% C4(X,Y,Z,W) clique of size 4.

E(Y,X) :- E(X,Y).
C2(X,Y) :- E(X,Y).
C2(Y,X) :- C2(X,Y).
C3(X,Y,Z) :- C2(X,Y), E(X,Z), E(Y,Z).
C3(X,Y,Z) :- C3(X,Y,Z).
C3(X,Z,Y) :- C3(X,Y,Z).
C3(Y,X,Z) :- C3(X,Y,Z).
C3(Y,Z,X) :- C3(X,Y,Z).
C3(Z,X,Y) :- C3(X,Y,Z).
C3(Z,Y,X) :- C3(X,Y,Z).
C4(X,Y,Z,W) :- C3(X,Y,Z), E(X,W), E(Y,W), E(Z,W).
C4(X,Y,Z,W) :- C4(X,Y,Z,W).
C4(X,Y,W,Z) :- C4(X,Y,Z,W).
C4(X,W,Y,Z) :- C4(X,Y,Z,W).
C4(X,W,Z,Y) :- C4(X,Y,Z,W).
C4(X,Z,W,Y) :- C4(X,Y,Z,W).
C4(X,Z,Y,W) :- C4(X,Y,Z,W).
C4(Y,X,Z,W) :- C4(X,Y,Z,W).
C4(Y,X,W,Z) :- C4(X,Y,Z,W).
C4(Y,W,X,Z) :- C4(X,Y,Z,W).
C4(Y,W,Z,X) :- C4(X,Y,Z,W).
C4(Y,Z,W,X) :- C4(X,Y,Z,W).
C4(Y,Z,X,W) :- C4(X,Y,Z,W).
C4(Z,Y,X,W) :- C4(X,Y,Z,W).
C4(Z,Y,W,X) :- C4(X,Y,Z,W).
C4(Z,W,X,Y) :- C4(X,Y,Z,W).
C4(Z,W,Y,X) :- C4(X,Y,Z,W).
C4(Z,X,Y,W) :- C4(X,Y,Z,W).
C4(Z,X,W,Y) :- C4(X,Y,Z,W).
C4(W,X,Z,Y) :- C4(X,Y,Z,W).
C4(W,X,Y,Z) :- C4(X,Y,Z,W).
C4(W,Z,Y,X) :- C4(X,Y,Z,W).
C4(W,Z,X,Y) :- C4(X,Y,Z,W).
C4(W,Y,X,Z) :- C4(X,Y,Z,W).
C4(W,Y,Z,X) :- C4(X,Y,Z,W).
Q3(A,B,C) :- C3(A,B,C), C2(A,D), Sp(A), Sp(D).
Q3(A,B,C)?
"""
output = """
#rewriting: 152
"""
