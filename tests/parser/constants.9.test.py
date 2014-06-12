input = """
%#const a = 10.
%#maxint = 1.
p(10).
a :- p(a).
"""
output = """
%#const a = 10.
%#maxint = 1.
p(10).
a :- p(a).
"""
