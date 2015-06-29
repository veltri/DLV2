input = """
a(1) | a(3).
a(2).
c(1,1).
c(1,3).
d(1,5).

b(X) :- a(X), c(Y,X).

ok :- #max{V :b(V)} < X, d(Y,X).
"""
output = """
a(1) | a(3).
a(2).
c(1,1).
c(1,3).
d(1,5).

b(X) :- a(X), c(Y,X).

ok :- #max{V :b(V)} < X, d(Y,X).
"""
