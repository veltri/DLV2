input = """
a(f(1)). 
a(f(f(2))).
a(f(f(f(3)))).
a(f(f(f(f(4))))).
a(f(f(f(f(f(5)))))).

a(X) :- a(f(f(X))).
"""
output = """
a(f(1)). 
a(f(f(2))).
a(f(f(f(3)))).
a(f(f(f(f(4))))).
a(f(f(f(f(f(5)))))).

a(X) :- a(f(f(X))).
"""
