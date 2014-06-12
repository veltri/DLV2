input = """
n(2).
a(X) :- X > 0, X < #sum{ Z : n(Z) }.

"""
output = """
n(2).
a(X) :- X > 0, X < #sum{ Z : n(Z) }.

"""
