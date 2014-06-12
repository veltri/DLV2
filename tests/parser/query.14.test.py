input = """
a | b.

a :- b.
b :- a.

c :- a.

b ? %a,b ?
"""
output = """
a | b.

a :- b.
b :- a.

c :- a.

b ? %a,b ?
"""
