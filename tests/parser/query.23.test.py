input = """
a | b | c.

a | b :- c.
a | c :- b.
b | c :- a.

a? %not a?

"""
output = """
a | b | c.

a | b :- c.
a | c :- b.
b | c :- a.

a? %not a?

"""
