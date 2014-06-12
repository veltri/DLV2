input = """
a(1).
a(2).
a(3).

p(1,3).
p(2,4). 

:- p(M, N), #count{V : a(V)} > N.
"""
output = """
a(1).
a(2).
a(3).

p(1,3).
p(2,4). 

:- p(M, N), #count{V : a(V)} > N.
"""
