input = """
true.
a :- true.
b :- a.

c :- not notc.
notc :- not c.
"""
output = """
true.
a :- true.
b :- a.

c :- not notc.
notc :- not c.
"""
