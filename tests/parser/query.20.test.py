input = """
a | b | c.

a | b :- c.
a | c :- b.
b | c :- a.

a?

"""
output = """
a | b | c.

a | b :- c.
a | c :- b.
b | c :- a.

a?

"""
