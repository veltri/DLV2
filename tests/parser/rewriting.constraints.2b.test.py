input = """
p(X) | q(Y) :- a(X,Y).
a(1,2).
a(2,1).
:- p(X), q(X).
"""
output = """
p(X) | q(Y) :- a(X,Y).
a(1,2).
a(2,1).
:- p(X), q(X).
"""
