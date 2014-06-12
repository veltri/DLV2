input = """
%#const pippo = "pippo".
p(pippo).
a(X) :- p(X).
"""
output = """
%#const pippo = "pippo".
p(pippo).
a(X) :- p(X).
"""
