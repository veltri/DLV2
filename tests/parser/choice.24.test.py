input = """
x(a) | x(b) | y.
x(a) | x(b) | y.
:- not y.
x(p) | x(q).
x(t) :- x(p).
x(t) :- x(q).
x(a) :- x(b), x(t).
x(b) :- x(a).
x(c) :- not x(a).
"""
output = """
x(a) | x(b) | y.
x(a) | x(b) | y.
:- not y.
x(p) | x(q).
x(t) :- x(p).
x(t) :- x(q).
x(a) :- x(b), x(t).
x(b) :- x(a).
x(c) :- not x(a).
"""
