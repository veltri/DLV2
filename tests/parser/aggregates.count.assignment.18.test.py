input = """

a(Z) :- #count{X: p(X,Z)} = Z.

p(1,1).
p(1,2).
p(2,1).
p(2,2).
p(3,5).

"""
output = """

a(Z) :- #count{X: p(X,Z)} = Z.

p(1,1).
p(1,2).
p(2,1).
p(2,2).
p(3,5).

"""
