input = """
c(1).
c(2).
c(3).

a(X) | -a(X) :- c(X).

maxim(X) :- a(X), #max{ D : a(D) } = X.
"""
output = """
c(1).
c(2).
c(3).

a(X) | -a(X) :- c(X).

maxim(X) :- a(X), #max{ D : a(D) } = X.
"""
