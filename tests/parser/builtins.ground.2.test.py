input = """
true.
a | b :- true, 1 < 2.
:- a.
"""
output = """
true.
a | b :- true, 1 < 2.
:- a.
"""
