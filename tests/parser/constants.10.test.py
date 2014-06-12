input = """
%#const a = 1.
%#const #maxint = 1.
p(1).
a :- p(a).
"""
output = """
%#const a = 1.
%#const #maxint = 1.
p(1).
a :- p(a).
"""
