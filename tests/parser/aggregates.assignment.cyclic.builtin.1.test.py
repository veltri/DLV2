input = """
q(1).
p(1,2).
%s(1..3).

r(Z) :- q(X), Z=X+Y, #count{H: s(H), p(H,Z)}=Y."""
output = """
q(1).
p(1,2).
%s(1..3).

r(Z) :- q(X), Z=X+Y, #count{H: s(H), p(H,Z)}=Y."""
