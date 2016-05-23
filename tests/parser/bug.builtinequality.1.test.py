input = """
% Bug.
% line 3: Rule is not safe.
% Aborting due to parser errors.

s(20).
q(X) :- s(X), Y < X , Y = 5.
q1(X) :- s(X), Y < X , Y = 5.

"""
output = """
% Bug.
% line 3: Rule is not safe.
% Aborting due to parser errors.

s(20).
q(X) :- s(X), Y < X , Y = 5.
q1(X) :- s(X), Y < X , Y = 5.

"""
