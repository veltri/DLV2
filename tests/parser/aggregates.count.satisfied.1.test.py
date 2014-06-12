input = """
c(1) | c(2).
a(X) :- c(X).
p(4).
okay(X) :- p(Y), c(X), #count{V : a(V)} <Y. 
"""
output = """
c(1) | c(2).
a(X) :- c(X).
p(4).
okay(X) :- p(Y), c(X), #count{V : a(V)} <Y. 
"""
