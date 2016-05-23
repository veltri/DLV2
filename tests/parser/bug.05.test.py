input = """
s :- a.
s :- b.

a :- true.
true.

false :- not true.
"""
output = """
s :- a.
s :- b.

a :- true.
true.

false :- not true.
"""
