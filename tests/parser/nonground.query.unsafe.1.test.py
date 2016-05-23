input = """
p(X) | q(X) :- a(X).

a(0).
a(1).

r.

r? %, not q(X)?
"""
output = """
p(X) | q(X) :- a(X).

a(0).
a(1).

r.

r? %, not q(X)?
"""
