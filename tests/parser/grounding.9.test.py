input = """
bottom(a,b).
bottom(b,c).
bottom(c,d).

pushable_bottom(b,c).

pushdown(B,C) | npushdown(B,C) :- bottom(a,B), box(B,0), pushable_bottom(B,C).


box(B,1) :- pushdown(_,B).
box(b,0).


good_pushlocation(c).

"""
output = """
bottom(a,b).
bottom(b,c).
bottom(c,d).

pushable_bottom(b,c).

pushdown(B,C) | npushdown(B,C) :- bottom(a,B), box(B,0), pushable_bottom(B,C).


box(B,1) :- pushdown(_,B).
box(b,0).


good_pushlocation(c).

"""
