input = """
p(X) :- q(Y). %, #succ(Y,X).
q(X) :- p(X).

q(0).
"""
output = """
p(X) :- q(Y). %, #succ(Y,X).
q(X) :- p(X).

q(0).
"""
