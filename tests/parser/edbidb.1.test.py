input = """
f(a) | f(b).
f(1).
f(d) :- f(a).
f(d) :- f(b).
f(2).
"""
output = """
f(a) | f(b).
f(1).
f(d) :- f(a).
f(d) :- f(b).
f(2).
"""
