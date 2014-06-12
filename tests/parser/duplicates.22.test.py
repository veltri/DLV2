input = """
a :- not b.

a :- not c.
         c :- not d.
                  d :- not b.
"""
output = """
a :- not b.

a :- not c.
         c :- not d.
                  d :- not b.
"""
