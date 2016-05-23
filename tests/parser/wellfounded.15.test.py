input = """
% test skip of Propagate_DeriveSingleUndefinedPosBodyLiteral()

a :- b.
b :- a.

a | b.

-a :- not a.
-b :- not b.

"""
output = """
% test skip of Propagate_DeriveSingleUndefinedPosBodyLiteral()

a :- b.
b :- a.

a | b.

-a :- not a.
-b :- not b.

"""
