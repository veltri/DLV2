input = """
a | b :- c.
a | b :- d.

c | d.

:- c, not d.
"""
output = """
a | b :- c.
a | b :- d.

c | d.

:- c, not d.
"""
