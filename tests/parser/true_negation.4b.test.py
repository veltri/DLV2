input = """
up(L,0) | -up(L,0) :- latch(L).

latch(a).
latch(b).
latch(c).
"""
output = """
up(L,0) | -up(L,0) :- latch(L).

latch(a).
latch(b).
latch(c).
"""
