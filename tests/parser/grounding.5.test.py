input = """
n(X1) :- n(X), succ(X,X1).
n(X):- n0(X).

n0(0).
succ(0,1).
succ(1,2).
succ(2,3).
succ(3,4).
succ(4,5).
"""
output = """
n(X1) :- n(X), succ(X,X1).
n(X):- n0(X).

n0(0).
succ(0,1).
succ(1,2).
succ(2,3).
succ(3,4).
succ(4,5).
"""
