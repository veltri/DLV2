input = """
e(0). e(1).
p(X) | q(X) :- e(X).
p(1) :- q(1).
q(1) :- p(1).
r :- p(X1), q(X1), p(X2), q(X2), p(X3), q(X3), p(X4), q(X4), p(X5),
q(X5), p(X6), q(X6), p(X7), q(X7).

"""
output = """
e(0). e(1).
p(X) | q(X) :- e(X).
p(1) :- q(1).
q(1) :- p(1).
r :- p(X1), q(X1), p(X2), q(X2), p(X3), q(X3), p(X4), q(X4), p(X5),
q(X5), p(X6), q(X6), p(X7), q(X7).

"""
