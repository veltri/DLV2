input = """
b(1). b(2).
c(a). c(b).
a(A,B) | na(A,B) :- c(A), b(B).
:- not 1=#count{A:a(A,B)}, b(B).
ad(A) :- a(A,_).
:- c(A), not ad(A).
"""
output = """
b(1). b(2).
c(a). c(b).
a(A,B) | na(A,B) :- c(A), b(B).
:- not 1=#count{A:a(A,B)}, b(B).
ad(A) :- a(A,_).
:- c(A), not ad(A).
"""
