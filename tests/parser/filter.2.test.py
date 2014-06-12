input = """
p(2) | f.
-p(1) :- true.

true.
:- f.
"""
output = """
p(2) | f.
-p(1) :- true.

true.
:- f.
"""
