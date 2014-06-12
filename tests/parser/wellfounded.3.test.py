input = """
a :- b.
b | c.

d.
:- d, a.
"""
output = """
a :- b.
b | c.

d.
:- d, a.
"""
