input = """
% Most of this example is due to Nicola Leone.
% It is a counterexample to why single-pass "positional" PT literal computation
% is not sound.

d | f.
q(1) :- d,f.
q(2) | p(2):- d,f.
v(Y) | p(Y) :- a(X,Y), q(X).
q(X) | v(X) :- a(X,_), p(X).
p(1) :- d,f.
t | p(4).

p(3) | p(1) :- t. 
 

a(1,2). 

"""
output = """
% Most of this example is due to Nicola Leone.
% It is a counterexample to why single-pass "positional" PT literal computation
% is not sound.

d | f.
q(1) :- d,f.
q(2) | p(2):- d,f.
v(Y) | p(Y) :- a(X,Y), q(X).
q(X) | v(X) :- a(X,_), p(X).
p(1) :- d,f.
t | p(4).

p(3) | p(1) :- t. 
 

a(1,2). 

"""
