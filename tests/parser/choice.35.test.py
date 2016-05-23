input = """
a | b :- d.

c | d.

:- c, not d.
"""
output = """
a | b :- d.

c | d.

:- c, not d.
"""
