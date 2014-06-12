input = """
%#maxint = 20.
n(2).
n(5).

a(X) :- X < #sum{ Z : n(Z) }. %#int(X), X < #times{ Z : n(Z) }.
b(X) :- X > #count{ Z : n(Z) }. %#int(X), X > #times{ Z : n(Z) }.

"""
output = """
%#maxint = 20.
n(2).
n(5).

a(X) :- X < #sum{ Z : n(Z) }. %#int(X), X < #times{ Z : n(Z) }.
b(X) :- X > #count{ Z : n(Z) }. %#int(X), X > #times{ Z : n(Z) }.

"""
