input = """
a(X) | b(Y) :- v (X,Y) .
 v(v ,v) | w(v,w) | v(w, v ).
"""
output = """
a(X) | b(Y) :- v (X,Y) .
 v(v ,v) | w(v,w) | v(w, v ).
"""
