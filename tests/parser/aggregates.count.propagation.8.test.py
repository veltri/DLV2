input = """
c(1) | c(2) | c(3).
a(X) :- c(X).

okay :- 0 < #count{V :a(V)} < 3. 
ouch :- 1 < #count{V :a(V)} < 3.
"""
output = """
c(1) | c(2) | c(3).
a(X) :- c(X).

okay :- 0 < #count{V :a(V)} < 3. 
ouch :- 1 < #count{V :a(V)} < 3.
"""
