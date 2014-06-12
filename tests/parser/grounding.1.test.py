input = """
p(a,b).

i(X) :- p(X,Y).

r(X,Y,X) :- i(X), i(Y).
"""
output = """
p(a,b).

i(X) :- p(X,Y).

r(X,Y,X) :- i(X), i(Y).
"""
