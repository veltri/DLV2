input = """
n(5).
n(4).
n(3).
n(2).
n(1).

eq(X,Y) :- n(X), n(Y), X=Y.
eq1(X,Y) :- n(X), n(Y), X=Y.
ne(X,Y) :- n(X), n(Y), X!=Y.
lt(X,Y) :- n(X), n(Y), X<Y.
gt(X,Y) :- n(X), n(Y), X>Y.
le(X,Y) :- n(X), n(Y), X<=Y.
ge(X,Y) :- n(X), n(Y), X>=Y.
"""
output = """
n(5).
n(4).
n(3).
n(2).
n(1).

eq(X,Y) :- n(X), n(Y), X=Y.
eq1(X,Y) :- n(X), n(Y), X=Y.
ne(X,Y) :- n(X), n(Y), X!=Y.
lt(X,Y) :- n(X), n(Y), X<Y.
gt(X,Y) :- n(X), n(Y), X>Y.
le(X,Y) :- n(X), n(Y), X<=Y.
ge(X,Y) :- n(X), n(Y), X>=Y.
"""
