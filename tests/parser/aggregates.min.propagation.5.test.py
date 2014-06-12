input = """
% Only undefined auxiliary atoms.
a(1) | b(1).
a(2) | b(2).
ok1 :- #min{V:a(V)} = 2.
"""
output = """
% Only undefined auxiliary atoms.
a(1) | b(1).
a(2) | b(2).
ok1 :- #min{V:a(V)} = 2.
"""
