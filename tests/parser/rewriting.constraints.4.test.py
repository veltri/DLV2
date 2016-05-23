input = """
a1(X) | a2(X) :- fact(X).

b1 | b2 | b3.

c1 | c2 | c3 | c4.

f1 | f2.
f2 | f1.

h | -h.

:- a1(X), a2(X), not h.
:- b1, b2.
:- b3, b1.
:- b2, not h, b3.
:- c3,c2,c1,c4, not f1, not f2.
:- f1,f2.

fact(a). fact(b). fact(c).

"""
output = """
a1(X) | a2(X) :- fact(X).

b1 | b2 | b3.

c1 | c2 | c3 | c4.

f1 | f2.
f2 | f1.

h | -h.

:- a1(X), a2(X), not h.
:- b1, b2.
:- b3, b1.
:- b2, not h, b3.
:- c3,c2,c1,c4, not f1, not f2.
:- f1,f2.

fact(a). fact(b). fact(c).

"""
