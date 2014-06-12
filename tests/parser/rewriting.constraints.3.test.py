input = """
f(X,Y) | g(X,Y) :- a(X,Y).

a(1,2).
a(2,1).

:- f(X,Y), g(Y,X).
"""
output = """
f(X,Y) | g(X,Y) :- a(X,Y).

a(1,2).
a(2,1).

:- f(X,Y), g(Y,X).
"""
