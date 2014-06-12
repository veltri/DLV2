input = """
f(1). f(2).

h(X) :- f(X).

a | b.

:- a, not 1 < #count{Z:f(Z)}.
"""
output = """
f(1). f(2).

h(X) :- f(X).

a | b.

:- a, not 1 < #count{Z:f(Z)}.
"""
