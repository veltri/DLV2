input = """
a :- b.
b :- a.
c | d.  
a :- not c.

a | z.

:- not a.
:- not z.

z :- y.
y :- z.
x | w.
z :- not x.
"""
output = """
a :- b.
b :- a.
c | d.  
a :- not c.

a | z.

:- not a.
:- not z.

z :- y.
y :- z.
x | w.
z :- not x.
"""
