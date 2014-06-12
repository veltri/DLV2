input = """
a :- b.
b :- a.
:- not a.

"""
output = """
a :- b.
b :- a.
:- not a.

"""
