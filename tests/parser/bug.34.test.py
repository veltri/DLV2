input = """
a :- not b.

c :- b.

:- not c.

"""
output = """
a :- not b.

c :- b.

:- not c.

"""
