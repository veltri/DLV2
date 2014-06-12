input = """
%#maxint=10.

%number(0..10).
q(C) :- number(C).
a | b :- p(A,B), q(C), r(X,A), q(X), not s(X), not t(C). 

p(1,1).
r(3,1).

s(5).
s(0).

t(0).
t(2).
"""
output = """
%#maxint=10.

%number(0..10).
q(C) :- number(C).
a | b :- p(A,B), q(C), r(X,A), q(X), not s(X), not t(C). 

p(1,1).
r(3,1).

s(5).
s(0).

t(0).
t(2).
"""
