input = """
a :- not b.
b :- not a.
c :- a.
d :- not c.

"""
output = """
a :- not b.
b :- not a.
c :- a.
d :- not c.

"""
