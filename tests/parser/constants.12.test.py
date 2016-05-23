input = """
%#const a = pippo.
p(a).
p(pippo).
a(X) :- p(X).
"""
output = """
%#const a = pippo.
p(a).
p(pippo).
a(X) :- p(X).
"""
