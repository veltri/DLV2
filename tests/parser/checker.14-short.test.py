input = """
a | b :- not c.
b :- d, not c.
e | a :- f.
g | d :- h.
i | g :- j.
e | a | k :- l.
l | e | a :- l, i.
j | not_i :- g.
c | m :- i.
h :- k.
n | i | e.
o | h.
o | p.
q | o | f.
q | n | c.
not_h | not_c.
g | r.

not_e :- not e.
not_a :- not a.
not_q :- not q.
not_b :- not b.
:- i, not_i.
:- c, not_c.

"""
output = """
a | b :- not c.
b :- d, not c.
e | a :- f.
g | d :- h.
i | g :- j.
e | a | k :- l.
l | e | a :- l, i.
j | not_i :- g.
c | m :- i.
h :- k.
n | i | e.
o | h.
o | p.
q | o | f.
q | n | c.
not_h | not_c.
g | r.

not_e :- not e.
not_a :- not a.
not_q :- not q.
not_b :- not b.
:- i, not_i.
:- c, not_c.

"""
