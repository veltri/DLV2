input = """
p(1) :- #count{X:q(X)}=1.
q(X) :- p(X).
"""
output = """
p(1) :- #count{X:q(X)}=1.
q(X) :- p(X).
"""
