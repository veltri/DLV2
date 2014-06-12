input = """
c | nc.

a(0) :- not c.
a(1) :- c.
good :- #min{ X: a(X) } = 1.

"""
output = """
c | nc.

a(0) :- not c.
a(1) :- c.
good :- #min{ X: a(X) } = 1.

"""
