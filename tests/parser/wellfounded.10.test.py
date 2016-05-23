input = """
t(Z) :- t0(Z).
t(Z) :- g(X,Y,Z), t(X), not t(Y).

t0(2).
g(5,1,3).
g(1,2,4).
g(3,4,5).

"""
output = """
t(Z) :- t0(Z).
t(Z) :- g(X,Y,Z), t(X), not t(Y).

t0(2).
g(5,1,3).
g(1,2,4).
g(3,4,5).

"""
