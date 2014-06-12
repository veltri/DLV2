input = """
d(1).
d(2).
d(3).

d(4) :- #max{V : d(V)} >= 3.

"""
output = """
d(1).
d(2).
d(3).

d(4) :- #max{V : d(V)} >= 3.

"""
