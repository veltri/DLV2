input = """
g(X) :- e(X), f(X).
f(0).

:- e(0).
"""
output = """
g(X) :- e(X), f(X).
f(0).

:- e(0).
"""
