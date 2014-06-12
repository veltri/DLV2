input = """
p(a) | p(b) :- #count{X:p(X)}>=1.
p(a) :- p(b).
p(b) :- p(a).

"""
output = """
p(a) | p(b) :- #count{X:p(X)}>=1.
p(a) :- p(b).
p(b) :- p(a).

"""
