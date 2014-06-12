input = """
%#const a =10.
%#const b=20. 

%#maxint=30.
p(X):-X=a+b.
"""
output = """
%#const a =10.
%#const b=20. 

%#maxint=30.
p(X):-X=a+b.
"""
