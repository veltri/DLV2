input = """
a :- not b.
a :- not c.
b :- not a.
c :- not a.
"""
output = """
a :- not b.
a :- not c.
b :- not a.
c :- not a.
"""
