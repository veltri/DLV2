input = """

a(Z) :- #count{X: p(X,Y)} = Z, q(Y),r(T).

p(1,1) | p(1,2).
q(1).
r(1).


"""
output = """

a(Z) :- #count{X: p(X,Y)} = Z, q(Y),r(T).

p(1,1) | p(1,2).
q(1).
r(1).


"""
