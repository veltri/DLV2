input = """
a(a).
b(1).
b(2).

cap(1).

all(X,Y) | nall(X,Y) :- a(X), b(Y).

:- #count{Y:all(a,Y)} > C, cap(C).
:- #count{Y:all(a,Y)} < C, cap(C).

"""
output = """
a(a).
b(1).
b(2).

cap(1).

all(X,Y) | nall(X,Y) :- a(X), b(Y).

:- #count{Y:all(a,Y)} > C, cap(C).
:- #count{Y:all(a,Y)} < C, cap(C).

"""
