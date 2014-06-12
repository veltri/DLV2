input = """
f(1). 
f(2).
f(3).

g(A,B,C,D,E) :- f(A), f(B), f(C), f(D), f(E).

"2b" | "not2b".
"""
output = """
f(1). 
f(2).
f(3).

g(A,B,C,D,E) :- f(A), f(B), f(C), f(D), f(E).

"2b" | "not2b".
"""
