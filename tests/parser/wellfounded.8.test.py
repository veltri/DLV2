input = """
a :- a.
a | b :- not a.

"""
output = """
a :- a.
a | b :- not a.

"""
