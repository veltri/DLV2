input = """
%#maxint=5.

% This is a slitherlink encoding.
plink(X1,Y,X2,Y) :- X2 <= D, dim(D), Y <= D. % #succ(X1,X2), X2 <= D, dim(D), #int(Y), Y <= D, #int(X1).
plink(X,Y1,X,Y2) :- Y2 <= D, dim(D), X <= D. % #succ(Y1,Y2), Y2 <= D, dim(D), #int(X), X <= D, #int(Y1).

link(X1,Y1,X2,Y2) | nlink(X1,Y1,X2,Y2) :- plink(X1,Y1,X2,Y2).

neighbor(X,Y,X1,Y1,X2,Y2) :- plink(X1,Y1,X2,Y2), digit(X,Y,D), Y1=Y, Y2=Y. %#succ(X1,X), digit(X,Y,D), Y1=Y, Y2=Y.
neighbor(X,Y,X1,Y1,X2,Y2) :- plink(X1,Y1,X2,Y2), digit(X,Y,D). %#succ(X1,X), digit(X,Y,D), #succ(Y1,Y), #succ(Y2,Y).
neighbor(X,Y,X1,Y1,X2,Y2) :- plink(X1,Y1,X2,Y2), digit(X,Y,D), X1=X, X2=X. %#succ(Y1,Y), digit(X,Y,D), X1=X, X2=X.
neighbor(X,Y,X1,Y1,X2,Y2) :- plink(X1,Y1,X2,Y2), digit(X,Y,D). %#succ(Y1,Y), digit(X,Y,D), #succ(X1,X), #succ(X2,X).

:- digit(X,Y,D), not #count{ X1,Y1,X2,Y2: neighbor(X,Y,X1,Y1,X2,Y2), link(X1,Y1,X2,Y2) } = D.

slink(X1,Y1,X2,Y2) :- link(X1,Y1,X2,Y2).
slink(X1,Y1,X2,Y2) :- link(X2,Y2,X1,Y1).

node(X,Y) :- slink(X,Y,_,_).

reach(X,Y,X,Y,X1,Y1) :- slink(X,Y,X1,Y1).
reach(X,Y,X1,Y1,X2,Y2) :- reach(X,Y,X3,Y3,X1,Y1), slink(X1,Y1,X2,Y2), nodediff(X2,Y2,X3,Y3).

nodediff(X1,Y1,X2,Y2) :- node(X1,Y1), node(X2,Y2), X1 != X2.
nodediff(X1,Y1,X2,Y2) :- node(X1,Y1), node(X2,Y2), Y1 != Y2.

reach1(X1,Y1,X2,Y2) :- reach(X1,Y1,_,_,X2,Y2).

:- node(X1,Y1), node(X2,Y2), not reach1(X1,Y1,X2,Y2).

:- node(X,Y), not #count{ X1,Y1: slink(X,Y,X1,Y1) } = 2.

% http://www.mathprog.org/Optima/Issues/optima69.pdf
dim(5).
digit(1,2,3).
digit(1,4,3).
digit(1,5,3).
digit(2,1,2).
digit(2,5,1).
digit(3,2,2).
digit(3,5,2).
digit(4,1,2).
digit(4,2,2).
digit(4,5,3).
digit(5,1,3).
digit(5,2,3).
digit(5,3,2).
"""
output = """
%#maxint=5.

% This is a slitherlink encoding.
plink(X1,Y,X2,Y) :- X2 <= D, dim(D), Y <= D. % #succ(X1,X2), X2 <= D, dim(D), #int(Y), Y <= D, #int(X1).
plink(X,Y1,X,Y2) :- Y2 <= D, dim(D), X <= D. % #succ(Y1,Y2), Y2 <= D, dim(D), #int(X), X <= D, #int(Y1).

link(X1,Y1,X2,Y2) | nlink(X1,Y1,X2,Y2) :- plink(X1,Y1,X2,Y2).

neighbor(X,Y,X1,Y1,X2,Y2) :- plink(X1,Y1,X2,Y2), digit(X,Y,D), Y1=Y, Y2=Y. %#succ(X1,X), digit(X,Y,D), Y1=Y, Y2=Y.
neighbor(X,Y,X1,Y1,X2,Y2) :- plink(X1,Y1,X2,Y2), digit(X,Y,D). %#succ(X1,X), digit(X,Y,D), #succ(Y1,Y), #succ(Y2,Y).
neighbor(X,Y,X1,Y1,X2,Y2) :- plink(X1,Y1,X2,Y2), digit(X,Y,D), X1=X, X2=X. %#succ(Y1,Y), digit(X,Y,D), X1=X, X2=X.
neighbor(X,Y,X1,Y1,X2,Y2) :- plink(X1,Y1,X2,Y2), digit(X,Y,D). %#succ(Y1,Y), digit(X,Y,D), #succ(X1,X), #succ(X2,X).

:- digit(X,Y,D), not #count{ X1,Y1,X2,Y2: neighbor(X,Y,X1,Y1,X2,Y2), link(X1,Y1,X2,Y2) } = D.

slink(X1,Y1,X2,Y2) :- link(X1,Y1,X2,Y2).
slink(X1,Y1,X2,Y2) :- link(X2,Y2,X1,Y1).

node(X,Y) :- slink(X,Y,_,_).

reach(X,Y,X,Y,X1,Y1) :- slink(X,Y,X1,Y1).
reach(X,Y,X1,Y1,X2,Y2) :- reach(X,Y,X3,Y3,X1,Y1), slink(X1,Y1,X2,Y2), nodediff(X2,Y2,X3,Y3).

nodediff(X1,Y1,X2,Y2) :- node(X1,Y1), node(X2,Y2), X1 != X2.
nodediff(X1,Y1,X2,Y2) :- node(X1,Y1), node(X2,Y2), Y1 != Y2.

reach1(X1,Y1,X2,Y2) :- reach(X1,Y1,_,_,X2,Y2).

:- node(X1,Y1), node(X2,Y2), not reach1(X1,Y1,X2,Y2).

:- node(X,Y), not #count{ X1,Y1: slink(X,Y,X1,Y1) } = 2.

% http://www.mathprog.org/Optima/Issues/optima69.pdf
dim(5).
digit(1,2,3).
digit(1,4,3).
digit(1,5,3).
digit(2,1,2).
digit(2,5,1).
digit(3,2,2).
digit(3,5,2).
digit(4,1,2).
digit(4,2,2).
digit(4,5,3).
digit(5,1,3).
digit(5,2,3).
digit(5,3,2).
"""
