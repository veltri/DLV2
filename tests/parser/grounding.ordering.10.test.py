input = """
g(1,2).
s(1).
f(X) :- s(Y), g(Y,X), T=1+2. 
"""
output = """
g(1,2).
s(1).
f(X) :- s(Y), g(Y,X), T=1+2. 
"""
