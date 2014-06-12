input = """
p(X) :- q(Y), r(Z), X=Y+Z.
q(X) :- p(X).
q(0).
r(5).
"""
output = """
p(X) :- q(Y), r(Z), X=Y+Z.
q(X) :- p(X).
q(0).
r(5).
"""
