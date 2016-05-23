input = """
block(a).
block(b).
block(c).
block(d).
block(e).
location(table).
location(B) :- block(B).
"""
output = """
block(a).
block(b).
block(c).
block(d).
block(e).
location(table).
location(B) :- block(B).
"""
