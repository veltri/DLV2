input = """
x(X) :- X != 1, X != 2. %, #succ(X,5).
"""
output = """
x(X) :- X != 1, X != 2. %, #succ(X,5).
"""
