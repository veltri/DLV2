input = """
a | b.
c | d.
a | c.

:- not c, a.
"""
output = """
a | b.
c | d.
a | c.

:- not c, a.
"""
