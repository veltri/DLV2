input = """
p(a) :- not #count{X:q(X)}<1.
q(X):- p(X).
"""
output = """
p(a) :- not #count{X:q(X)}<1.
q(X):- p(X).
"""
