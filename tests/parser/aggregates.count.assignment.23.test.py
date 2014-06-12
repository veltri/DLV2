input = """

a(Z) :- q(Y), r(Y,H), #count{X: p(X,Z)} = Z.

r(1,1).
q(1).
p(1,1).
p(1,2).
p(2,1).
p(2,2).
p(3,5).

"""
output = """

a(Z) :- q(Y), r(Y,H), #count{X: p(X,Z)} = Z.

r(1,1).
q(1).
p(1,1).
p(1,2).
p(2,1).
p(2,2).
p(3,5).

"""
