input = """
a :- not b.

c :- not a.

c :- b.

c?

"""
output = """
a :- not b.

c :- not a.

c :- b.

c?

"""
