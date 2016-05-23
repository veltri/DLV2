input = """
%#const a = 10.
%#const a = 20.
p(10).
a :- p(a).
"""
output = """
%#const a = 10.
%#const a = 20.
p(10).
a :- p(a).
"""
