input = """
f(X,1) :- a(X,Y),
          g(A),g(B),
          not f(1,X).

a(X,Y) :- g(X),g(Y).

g(x1).
g(x2).

"""
output = """
f(X,1) :- a(X,Y),
          g(A),g(B),
          not f(1,X).

a(X,Y) :- g(X),g(Y).

g(x1).
g(x2).

"""
