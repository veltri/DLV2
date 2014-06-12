input = """
f(a) :- not f(b).
f(b) :- not f(a).

edb(a).
f(c) :- edb(a).
"""
output = """
f(a) :- not f(b).
f(b) :- not f(a).

edb(a).
f(c) :- edb(a).
"""
