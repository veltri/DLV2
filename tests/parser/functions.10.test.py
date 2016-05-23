input = """
a(f(1)). 
a(f(f(2))).

a(X) | b(X) :- a(f(X)).

a(f(X))? %,b(X)?
"""
output = """
a(f(1)). 
a(f(f(2))).

a(X) | b(X) :- a(f(X)).

a(f(X))? %,b(X)?
"""
