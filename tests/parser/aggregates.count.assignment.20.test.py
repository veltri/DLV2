input = """

a(Z) :- #count{X: p(X,Y)} = Z.

p(1,1) | p(1,2).



"""
output = """

a(Z) :- #count{X: p(X,Y)} = Z.

p(1,1) | p(1,2).



"""
