input = """
:- a.
:- not b.
a :- b.

a | b :- c.
c | d.
"""
output = """
:- a.
:- not b.
a :- b.

a | b :- c.
c | d.
"""
