input = """
% Inferences from constraints.

b | a.

x :- a.
y :- x.

:- a, y.
"""
output = """
% Inferences from constraints.

b | a.

x :- a.
y :- x.

:- a, y.
"""
