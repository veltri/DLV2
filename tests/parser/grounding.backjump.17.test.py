input = """
block(1).
block(2).
block(3).
block(4).

p(1,1,5).
p(1,1,6).
p(2,2,3).
p(2,3,1).
q(X) :- block(B), block(L), #count{Y:p(B,L,Y)}=X.
"""
output = """
block(1).
block(2).
block(3).
block(4).

p(1,1,5).
p(1,1,6).
p(2,2,3).
p(2,3,1).
q(X) :- block(B), block(L), #count{Y:p(B,L,Y)}=X.
"""
