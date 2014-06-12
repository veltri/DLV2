input = """
n(2).
a(X) :-  X < #count{ Z : n(Z) }.

"""
output = """
n(2).
a(X) :-  X < #count{ Z : n(Z) }.

"""
