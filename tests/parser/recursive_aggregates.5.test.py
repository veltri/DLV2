input = """
d(1).
d(2).
d(3).

p(5).
p(6).

d(4) :- #max{V : d(V)} > 3.

p(7) :- #count{X : p(X)} > 2.

"""
output = """
d(1).
d(2).
d(3).

p(5).
p(6).

d(4) :- #max{V : d(V)} > 3.

p(7) :- #count{X : p(X)} > 2.

"""
