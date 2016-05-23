input = """
% Computes the minimum spanning tree by a weighted graph by using Prim
% algorithm.
% Version with weakconstraints with ground weights.
root(a).
node(a). node(b). node(c). node(d). node(e).
edge(a,b). edge(a,c). edge(c,b). edge(c,d). edge(b,e). edge(d,e).

in_tree(X,Y) | out_tree(X,Y) :- edge(X,Y),reached(X).
:- root(X), in_tree(_,X).
:- in_tree(X,Y), in_tree(Z,Y), X != Z.

reached(X):- root(X).
reached(Y):- reached(X), in_tree(X,Y).
:-node(X), not reached(X).

%:- in_tree(a,b). [4:1]
%:- in_tree(a,c). [3:1]
%:- in_tree(c,b). [2:1]
%:- in_tree(c,d). [3:1]
%:- in_tree(b,e). [4:1]
%:- in_tree(d,e). [5:1]





"""
output = """
% Computes the minimum spanning tree by a weighted graph by using Prim
% algorithm.
% Version with weakconstraints with ground weights.
root(a).
node(a). node(b). node(c). node(d). node(e).
edge(a,b). edge(a,c). edge(c,b). edge(c,d). edge(b,e). edge(d,e).

in_tree(X,Y) | out_tree(X,Y) :- edge(X,Y),reached(X).
:- root(X), in_tree(_,X).
:- in_tree(X,Y), in_tree(Z,Y), X != Z.

reached(X):- root(X).
reached(Y):- reached(X), in_tree(X,Y).
:-node(X), not reached(X).

%:- in_tree(a,b). [4:1]
%:- in_tree(a,c). [3:1]
%:- in_tree(c,b). [2:1]
%:- in_tree(c,d). [3:1]
%:- in_tree(b,e). [4:1]
%:- in_tree(d,e). [5:1]





"""
