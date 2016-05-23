input = """
a | b | c.

a | b :- c.
a | c :- b.
b | c :- a.

c?

"""
output = """
a | b | c.

a | b :- c.
a | c :- b.
b | c :- a.

c?

"""
