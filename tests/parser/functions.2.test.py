input = """
ok(X) :- p(X), q(X).
q(X) :- p(X).

p(f(a)).
"""
output = """
ok(X) :- p(X), q(X).
q(X) :- p(X).

p(f(a)).
"""
