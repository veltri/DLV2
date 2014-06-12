input = """
q(X) :- p(f(X)).
p(f(X)) :- r(X), q(X).

q(a).
r(a).
"""
output = """
q(X) :- p(f(X)).
p(f(X)) :- r(X), q(X).

q(a).
r(a).
"""
