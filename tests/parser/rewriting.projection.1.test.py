input = """
% Test with overly long identifiers (generated by the rewriting).

f(X,1) :- abcdefghijklmnopqrstuvwxyz(_,_,_,_,_,_,_,_,X),
          g(A), g(B),
          not f(1,X).

abcdefghijklmnopqrstuvwxyz(X,2,3,4,5,6,7,8,X) :- g(X).

g(x1).
g(x2).

"""
output = """
% Test with overly long identifiers (generated by the rewriting).

f(X,1) :- abcdefghijklmnopqrstuvwxyz(_,_,_,_,_,_,_,_,X),
          g(A), g(B),
          not f(1,X).

abcdefghijklmnopqrstuvwxyz(X,2,3,4,5,6,7,8,X) :- g(X).

g(x1).
g(x2).

"""
