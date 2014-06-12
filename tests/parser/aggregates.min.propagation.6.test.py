input = """
arc(a,b,2).
arc(a,c,3).
arc(b,d,3).
arc(c,d,2).
arc(d,a,2).

% maxint is deliberately set too large to detect wrong minima.

%#maxint=20.
path(X,Y,C) :- arc(X,Y,C).
path(X,Y,C) :- arc(X,Z,C1), path(Z,Y,C2), C = C1 + C2.

minpath(X,Y,C) :- path(X,Y,C), C = #min{ C1: path(X,Y,C1) }.

"""
output = """
arc(a,b,2).
arc(a,c,3).
arc(b,d,3).
arc(c,d,2).
arc(d,a,2).

% maxint is deliberately set too large to detect wrong minima.

%#maxint=20.
path(X,Y,C) :- arc(X,Y,C).
path(X,Y,C) :- arc(X,Z,C1), path(Z,Y,C2), C = C1 + C2.

minpath(X,Y,C) :- path(X,Y,C), C = #min{ C1: path(X,Y,C1) }.

"""
