input = """
a | na.
b | nb.
c | nc.
d | nd.
x | nx.

x :- w.
nx :- w.

w :- na, nc, nx.
w :- nb, c, nx.
w :- b, nd.
w :- not w.
"""
output = """
a | na.
b | nb.
c | nc.
d | nd.
x | nx.

x :- w.
nx :- w.

w :- na, nc, nx.
w :- nb, c, nx.
w :- b, nd.
w :- not w.
"""
