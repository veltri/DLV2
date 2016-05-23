input = """
:- not a.
a :- c.
c | b | e.
c | b.
d | e.
:- a, d, e.
"""
output = """
:- not a.
a :- c.
c | b | e.
c | b.
d | e.
:- a, d, e.
"""
