input = """

g(1).
g(2).
g(3).

f(a,b).
f(A,B):- g(A), g(B).
f(a,a).

"""
output = """

g(1).
g(2).
g(3).

f(a,b).
f(A,B):- g(A), g(B).
f(a,a).

"""
