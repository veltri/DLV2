input = """
a | b :- c.
-b :- a.

a | c.
"""
output = """
a | b :- c.
-b :- a.

a | c.
"""
