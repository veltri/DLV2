input = """
%f(1..2).
f(4).
g(X) :- f(X).
"""
output = """
%f(1..2).
f(4).
g(X) :- f(X).
"""
