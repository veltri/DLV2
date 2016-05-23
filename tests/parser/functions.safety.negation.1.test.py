input = """
p(X) :- q(f(X)), not r(f(X)).

q(f(a)).
r(a).
"""
output = """
p(X) :- q(f(X)), not r(f(X)).

q(f(a)).
r(a).
"""
