input = """
ok:-q(Y,X), not #count{V: a(V)}<1, not r(Y), #count{V:b(V)}>=1.

a(1) | a(2).
b(1) | b(2).

r(2).
q(1,2).
"""
output = """
ok:-q(Y,X), not #count{V: a(V)}<1, not r(Y), #count{V:b(V)}>=1.

a(1) | a(2).
b(1) | b(2).

r(2).
q(1,2).
"""
