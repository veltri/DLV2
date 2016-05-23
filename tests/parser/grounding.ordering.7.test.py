input = """
%#maxint=0.
f(Z):- Z=Y+0. %, #int(Y).
"""
output = """
%#maxint=0.
f(Z):- Z=Y+0. %, #int(Y).
"""
