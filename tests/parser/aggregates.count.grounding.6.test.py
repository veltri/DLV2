input = """
b(1).
c(a).
a(A,B) | na(A,B) :- c(A), b(B).
:- 1 < #count{A:a(A,1)}.

"""
output = """
b(1).
c(a).
a(A,B) | na(A,B) :- c(A), b(B).
:- 1 < #count{A:a(A,1)}.

"""
