input = """
b :- not a, not x.
a :- not b, not y.

x :- not b.
y :- not a.
"""
output = """
b :- not a, not x.
a :- not b, not y.

x :- not b.
y :- not a.
"""
