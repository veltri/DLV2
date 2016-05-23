input = """
t(Z) :- t0(Z).
t(Z) :- g(X,Y,Z), t(X).
t(Z) :- g(X,Y,Z), not t(Y).

t0(1).
g(1,2,3).
g(2,5,4).
g(2,4,5).
g(5,3,6).

"""
output = """
t(Z) :- t0(Z).
t(Z) :- g(X,Y,Z), t(X).
t(Z) :- g(X,Y,Z), not t(Y).

t0(1).
g(1,2,3).
g(2,5,4).
g(2,4,5).
g(5,3,6).

"""
