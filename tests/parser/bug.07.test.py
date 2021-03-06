input = """
a(1).
a(2).
b(1,2).
c(2).
c(3).

q(X,Y) :- a(X), c(Y).

p(X,Y,Z) :- a(X), q(Y,Z), m(X,Z).

m(X,Y) :- a(Z), p(Z,X,Y).

m(X,Y) :- b(X,Y), not n(X,Y).

n(X,Y) :- q(X,Y).

n(X,Y) :- b(X,Y), m(X,Y).
"""
output = """
a(1).
a(2).
b(1,2).
c(2).
c(3).

q(X,Y) :- a(X), c(Y).

p(X,Y,Z) :- a(X), q(Y,Z), m(X,Z).

m(X,Y) :- a(Z), p(Z,X,Y).

m(X,Y) :- b(X,Y), not n(X,Y).

n(X,Y) :- q(X,Y).

n(X,Y) :- b(X,Y), m(X,Y).
"""
