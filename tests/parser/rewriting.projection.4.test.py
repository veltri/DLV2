input = """
f(X,1) :- a(X,Y),
          g(A,X),g(B,X),
          not f(1,X).

a(X,Y) :- g(X,0),g(Y,0).

g(x1,0).
g(x2,0).

"""
output = """
f(X,1) :- a(X,Y),
          g(A,X),g(B,X),
          not f(1,X).

a(X,Y) :- g(X,0),g(Y,0).

g(x1,0).
g(x2,0).

"""
