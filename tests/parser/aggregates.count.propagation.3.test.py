input = """
a(1) | a(2).

a(3) | a(4).

ok :- 2 <= #count{V : a(V)} <= 2.
"""
output = """
a(1) | a(2).

a(3) | a(4).

ok :- 2 <= #count{V : a(V)} <= 2.
"""
