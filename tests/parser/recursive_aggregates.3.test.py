input = """
d(1).
d(2).
d(3).

d(4) :- #count{V : d(V)} > 2.

"""
output = """
d(1).
d(2).
d(3).

d(4) :- #count{V : d(V)} > 2.

"""
