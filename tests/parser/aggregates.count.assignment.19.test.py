input = """

a(Z,Y) :- #count{X: p(X,Y)} = Z, #count{W: p(W,Z)} = Y.

p(1,1).
p(1,2).
p(2,1).
p(2,2).
p(3,5).

"""
output = """

a(Z,Y) :- #count{X: p(X,Y)} = Z, #count{W: p(W,Z)} = Y.

p(1,1).
p(1,2).
p(2,1).
p(2,2).
p(3,5).

"""
