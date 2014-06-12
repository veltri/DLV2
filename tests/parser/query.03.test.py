input = """
a :- not b.

c :- not a.

c :- b.

b?

"""
output = """
a :- not b.

c :- not a.

c :- b.

b?

"""
