input = """
:- not a.
a | a :- b.
b :- not a.
"""
output = """
:- not a.
a | a :- b.
b :- not a.
"""
