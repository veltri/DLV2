input = """
%#const a = a.
p(a).
a :- p(a).
"""
output = """
%#const a = a.
p(a).
a :- p(a).
"""
