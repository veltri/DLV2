input = """
%#maxint=0.
f(X,Y):- 0=Y+X. %, #int(Y), #int(X).
"""
output = """
%#maxint=0.
f(X,Y):- 0=Y+X. %, #int(Y), #int(X).
"""
