input = """
a(1).
a(2) | a(3).
ok1 :- #max{V:a(V)} = 3.


b(3).
b(1) | b(2).
ok2 :- #max{V:b(V)} = 3.
"""
output = """
a(1).
a(2) | a(3).
ok1 :- #max{V:a(V)} = 3.


b(3).
b(1) | b(2).
ok2 :- #max{V:b(V)} = 3.
"""
