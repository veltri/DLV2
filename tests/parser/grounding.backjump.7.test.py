input = """
t(Y) :- p(X), #count{T:p(X),q(X,T)}=Y.
p(1).
p(2).
q(1,1).
q(1,2).
q(2,2).
q(2,3).
q(2,4).

"""
output = """
t(Y) :- p(X), #count{T:p(X),q(X,T)}=Y.
p(1).
p(2).
q(1,1).
q(1,2).
q(2,2).
q(2,3).
q(2,4).

"""
