input = """
pacifist(X)  :- quaker(X), not militarist(X).
militarist(X) :- republican(X), not pacifist(X).


republican(nixon).
quaker(nixon).
"""
output = """
pacifist(X)  :- quaker(X), not militarist(X).
militarist(X) :- republican(X), not pacifist(X).


republican(nixon).
quaker(nixon).
"""
