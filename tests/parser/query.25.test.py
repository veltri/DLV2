input = """
a | b | c.

a | b :- c.
a | c :- b.
b | c :- a.

c? %not c?

"""
output = """
a | b | c.

a | b :- c.
a | c :- b.
b | c :- a.

c? %not c?

"""
