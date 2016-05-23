input = """
% Show the necessity for the patch in rewrite.C 1.8. Our old and simple
% projection algorithm would sometimes generate incorrect results in the
% presence of multiple variable instances or constants.

q(1,2,3,4).
r(1,3).
r(1,4).

p(X,Z) :- q(X,Y,Z,Y), r(X,Z).                                                   
s(X,Z) :- q(X,Y,Z,U), r(X,Z), r(X,U).

t(X) :- q(X,Y,Z,4), r(X,Z).
u(X) :- q(X,Y,Z,4), r(X,Z), Y < 3.
"""
output = """
% Show the necessity for the patch in rewrite.C 1.8. Our old and simple
% projection algorithm would sometimes generate incorrect results in the
% presence of multiple variable instances or constants.

q(1,2,3,4).
r(1,3).
r(1,4).

p(X,Z) :- q(X,Y,Z,Y), r(X,Z).                                                   
s(X,Z) :- q(X,Y,Z,U), r(X,Z), r(X,U).

t(X) :- q(X,Y,Z,4), r(X,Z).
u(X) :- q(X,Y,Z,4), r(X,Z), Y < 3.
"""
