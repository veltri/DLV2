input = """
a :- not b.
b :- not a.

a :- not c.
c :- not a.
"""
output = """
a :- not b.
b :- not a.

a :- not c.
c :- not a.
"""
