input = """
%#const a=1.
%#maxint=2.
p(a) :- X=a. %#int(X), X=a.
"""
output = """
%#const a=1.
%#maxint=2.
p(a) :- X=a. %#int(X), X=a.
"""
