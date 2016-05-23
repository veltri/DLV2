input = """
a(1).
a(2).
a(3).
b(1).
b(3).
c(1,2).
c(2,3).

p(X) | q(Y) :- a(X), b(Y), not c(X,Y).
p(X) :- q(X).
"""
output = """
a(1).
a(2).
a(3).
b(1).
b(3).
c(1,2).
c(2,3).

p(X) | q(Y) :- a(X), b(Y), not c(X,Y).
p(X) :- q(X).
"""
