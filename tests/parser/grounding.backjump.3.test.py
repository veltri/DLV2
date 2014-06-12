input = """
%This is an example where we can not eliminate the duplicates of the rules.

%#maxint=8.
 
p(X) | r(X) :- q(X,Y), q(A,B), s(X,A), s(Y,B).

q(1,3).
q(2,4).
q(2,7).
q(3,8).
q(3,5).
q(1,6).

s(0,1).
s(1,2).
s(2,3).
s(3,4).
s(4,5).
s(5,6).
s(6,7).
s(7,8).
"""
output = """
%This is an example where we can not eliminate the duplicates of the rules.

%#maxint=8.
 
p(X) | r(X) :- q(X,Y), q(A,B), s(X,A), s(Y,B).

q(1,3).
q(2,4).
q(2,7).
q(3,8).
q(3,5).
q(1,6).

s(0,1).
s(1,2).
s(2,3).
s(3,4).
s(4,5).
s(5,6).
s(6,7).
s(7,8).
"""
