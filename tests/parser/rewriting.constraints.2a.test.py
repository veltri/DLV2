input = """
p(X) | -p(Y) :- a(X,Y).
a(1,2).
a(2,1).
"""
output = """
p(X) | -p(Y) :- a(X,Y).
a(1,2).
a(2,1).
"""
