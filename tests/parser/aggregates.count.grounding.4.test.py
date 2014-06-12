input = """
b(1). b(2).
c(a). c(b).
a(A,B) | na(A,B) :- c(A), b(B).
:- 1 < #count{A:a(A,B)}, b(B).
"""
output = """
b(1). b(2).
c(a). c(b).
a(A,B) | na(A,B) :- c(A), b(B).
:- 1 < #count{A:a(A,B)}, b(B).
"""
