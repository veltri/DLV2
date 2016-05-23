input = """
%#const a = 10.
a(a).

a(X) :- p(X).
p(a).
"""
output = """
%#const a = 10.
a(a).

a(X) :- p(X).
p(a).
"""
