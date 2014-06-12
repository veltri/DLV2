input = """
ok:-q(Y,X), p(Z,T), not #count{V: a(V)}<Y, not s(Z,T), not r(Y), #count{V:b(V)}>=1, not #count{V:a(V)}<X.

a(1) | a(2).
b(1) | b(2).

p(1,2).
s(2,3).
r(2).
q(1,2).
"""
output = """
ok:-q(Y,X), p(Z,T), not #count{V: a(V)}<Y, not s(Z,T), not r(Y), #count{V:b(V)}>=1, not #count{V:a(V)}<X.

a(1) | a(2).
b(1) | b(2).

p(1,2).
s(2,3).
r(2).
q(1,2).
"""
