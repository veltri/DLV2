input = """
% the input relation "arc" should be symmetric,
% or it should be made symmetric by adding rule
% arc(X,Y):- arc(Y,X).

in_hm(X,Y) | out_hm(X,Y) :- start(X), arc(X,Y).
in_hm(X,Y) | out_hm(X,Y) :- reached(X), arc(X,Y).

reached(Y) :- in_hm(_,Y).

:- in_hm(X,Y), in_hm(X,Y1), Y != Y1.
:- in_hm(X,Y), in_hm(X1,Y), X != X1.

:- arc(X,_), not reached(X).

% start -- the initial node of the path, and
% arc -- specifying the input graph
% should be provided in the EDB.
"""
output = """
% the input relation "arc" should be symmetric,
% or it should be made symmetric by adding rule
% arc(X,Y):- arc(Y,X).

in_hm(X,Y) | out_hm(X,Y) :- start(X), arc(X,Y).
in_hm(X,Y) | out_hm(X,Y) :- reached(X), arc(X,Y).

reached(Y) :- in_hm(_,Y).

:- in_hm(X,Y), in_hm(X,Y1), Y != Y1.
:- in_hm(X,Y), in_hm(X1,Y), X != X1.

:- arc(X,_), not reached(X).

% start -- the initial node of the path, and
% arc -- specifying the input graph
% should be provided in the EDB.
"""
