input = """
p(a) | p(b).
q(X) :- #count{ Y:p(Y) } = X.

"""
output = """
p(a) | p(b).
q(X) :- #count{ Y:p(Y) } = X.

"""
