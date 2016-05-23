input = """
bottom(b).
time0(0).

pushable_bottom(b,c).

pushdown(B,C) | npushdown(B,C) :- bottom(B), time0(T), box(B,T), pushable_bottom(B,C).


box(B,1) :- pushdown(_,B).
box(b,0).



"""
output = """
bottom(b).
time0(0).

pushable_bottom(b,c).

pushdown(B,C) | npushdown(B,C) :- bottom(B), time0(T), box(B,T), pushable_bottom(B,C).


box(B,1) :- pushdown(_,B).
box(b,0).



"""
