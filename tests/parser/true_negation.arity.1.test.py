input = """
% test 1
-p :- p(1).
q :- -q(1).
r(1) :- -r.
-s(1) :- s.

% test 2
t(1) :- not -t.
-u(1) :- not u.

% test 3
f(2).
g(1).
-f(X,X) :- g(X).

% test 4
mana(a).
-nemo.
nemo(X) :- mana(X).
"""
output = """
% test 1
-p :- p(1).
q :- -q(1).
r(1) :- -r.
-s(1) :- s.

% test 2
t(1) :- not -t.
-u(1) :- not u.

% test 3
f(2).
g(1).
-f(X,X) :- g(X).

% test 4
mana(a).
-nemo.
nemo(X) :- mana(X).
"""
