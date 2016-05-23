input = """
a | b | c.

a | b :- c.
a | c :- b.
b | c :- a.

b? %not b?

"""
output = """
a | b | c.

a | b :- c.
a | c :- b.
b | c :- a.

b? %not b?

"""
