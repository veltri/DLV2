input = """
%#const pippo = pippo.
%#const pippo = 2. 
p(pippo).
a(X) :- p(X).
"""
output = """
%#const pippo = pippo.
%#const pippo = 2. 
p(pippo).
a(X) :- p(X).
"""
