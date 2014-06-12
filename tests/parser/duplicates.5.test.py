input = """
b :- not a, not x. 
a :- not b, not y.

x :- not b, not p.
x :- not b, not q.
y :- not a, not p.
y :- not a, not q.


true.
r :- true.

p | q | r.
"""
output = """
b :- not a, not x. 
a :- not b, not y.

x :- not b, not p.
x :- not b, not q.
y :- not a, not p.
y :- not a, not q.


true.
r :- true.

p | q | r.
"""
