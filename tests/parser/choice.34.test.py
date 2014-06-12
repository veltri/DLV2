input = """
a | b :- d.
a | b :- c.

d :- not c.
c :- not d.

:- d, not c.
"""
output = """
a | b :- d.
a | b :- c.

d :- not c.
c :- not d.

:- d, not c.
"""
