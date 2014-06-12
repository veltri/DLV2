input = """
q(1,2).
%p(1..2).
%s(1..3).

%r(Z) :- #succ(X,Y), #count{H: s(H), not q(H,Y)}=Z, #count{F: p(F)}=G, X=G*3.
r(Z) :- #count{H: s(H), q(H,Y)}=Z, #count{F: p(F)}=G, X=G*3. """
output = """
q(1,2).
%p(1..2).
%s(1..3).

%r(Z) :- #succ(X,Y), #count{H: s(H), not q(H,Y)}=Z, #count{F: p(F)}=G, X=G*3.
r(Z) :- #count{H: s(H), q(H,Y)}=Z, #count{F: p(F)}=G, X=G*3. """
