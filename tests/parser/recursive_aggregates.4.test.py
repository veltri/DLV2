input = """
d(1).
d(2).
d(3).

d(4) :- 4 <= #count{V : d(V)} <= 4.

"""
output = """
d(1).
d(2).
d(3).

d(4) :- 4 <= #count{V : d(V)} <= 4.

"""
