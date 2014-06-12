input = """
%#maxint=2.
a(1).
b(1).
dummy :- a(A), b(B), A=B+C. % +(A,B,C), #int(A).
"""
output = """
%#maxint=2.
a(1).
b(1).
dummy :- a(A), b(B), A=B+C. % +(A,B,C), #int(A).
"""
