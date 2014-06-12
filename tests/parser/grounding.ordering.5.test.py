input = """
%#maxint=0.
f(Z) :- Z=X*Y. %#int(X), #int(Y), Z=X*Y.
"""
output = """
%#maxint=0.
f(Z) :- Z=X*Y. %#int(X), #int(Y), Z=X*Y.
"""
