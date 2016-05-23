input = """
a(S) :- q(Y), p(X), #count{H: b(H,Y)}=Z, t(Z,X,S).

q(1).
q(2).
p(1).
p(2).
b(1,1).
t(1,1,2).
t(1,2,3).
"""
output = """
a(S) :- q(Y), p(X), #count{H: b(H,Y)}=Z, t(Z,X,S).

q(1).
q(2).
p(1).
p(2).
b(1,1).
t(1,1,2).
t(1,2,3).
"""
