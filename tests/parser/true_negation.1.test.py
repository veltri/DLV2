input = """
true | -a :- not b.
true |  b :- not -a.

-true.
"""
output = """
true | -a :- not b.
true |  b :- not -a.

-true.
"""
