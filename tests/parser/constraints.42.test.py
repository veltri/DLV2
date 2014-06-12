input = """
% Inferences from constraints.

b | a.

x :- a.
y :- x.

:- not a, y.
"""
output = """
% Inferences from constraints.

b | a.

x :- a.
y :- x.

:- not a, y.
"""
