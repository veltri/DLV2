input = """
a | b | c.

a | b :- c.
a | c :- b.
b | c :- a.

b?

"""
output = """
a | b | c.

a | b :- c.
a | c :- b.
b | c :- a.

b?

"""
