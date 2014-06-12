input = """
:- not b.
b :- a, not a.
a | c.
"""
output = """
:- not b.
b :- a, not a.
a | c.
"""
