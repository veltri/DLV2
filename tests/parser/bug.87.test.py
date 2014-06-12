input = """
b(1). 
c | d :- #count{ X :  b(X), X < 3 } > 0.

"""
output = """
b(1). 
c | d :- #count{ X :  b(X), X < 3 } > 0.

"""
