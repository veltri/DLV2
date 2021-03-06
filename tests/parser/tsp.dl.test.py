input = """
% Travelling Salesman Problem

% Edges of graph.
edge(a,b,1).
edge(a,c,3).
edge(b,d,3).
edge(b,c,1).
edge(c,d,3).

% Starting node.
start(a).

% Node of graph
node(X) :- edge(X,_,_).
node(X) :- edge(_,X,_).


in(X,Y,C) | -in(X,Y,C) :- edge(X,Y,C).

reached(X):- start(X).
reached(X):- reached(Y), in(Y,X,C).

% Each node must be reached.
:- node(X), not reached(X).

% Cost of each edge in minimum path.
%:- in(X,Y,C). [C:1]

:- in(X,Y,C), in(X,Y1,C1), Y != Y1.
:- in(X1,Y,C), in(X,Y,C1), X != X1.
"""
output = """
% Travelling Salesman Problem

% Edges of graph.
edge(a,b,1).
edge(a,c,3).
edge(b,d,3).
edge(b,c,1).
edge(c,d,3).

% Starting node.
start(a).

% Node of graph
node(X) :- edge(X,_,_).
node(X) :- edge(_,X,_).


in(X,Y,C) | -in(X,Y,C) :- edge(X,Y,C).

reached(X):- start(X).
reached(X):- reached(Y), in(Y,X,C).

% Each node must be reached.
:- node(X), not reached(X).

% Cost of each edge in minimum path.
%:- in(X,Y,C). [C:1]

:- in(X,Y,C), in(X,Y1,C1), Y != Y1.
:- in(X1,Y,C), in(X,Y,C1), X != X1.
"""
