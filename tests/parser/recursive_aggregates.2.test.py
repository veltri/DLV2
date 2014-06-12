input = """
d(1).
d(2).
d(3).

d(4) :- #min{V : d(V)} = 1.

"""
output = """
d(1).
d(2).
d(3).

d(4) :- #min{V : d(V)} = 1.

"""
