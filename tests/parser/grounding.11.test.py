input = """
bottom(b).
time0(0).
time1(1).

pushable_bottom(b,c).

pushdown(B,C) | npushdown(B,C) :- bottom(B), time0(T), box(B,T), pushable_bottom(B,C).


box(B,T) :- pushdown(_,B), time1(T).
box(B,T) :- boxinit(B,T).
boxinit(b,0).


good_pushlocation(c).

"""
output = """
bottom(b).
time0(0).
time1(1).

pushable_bottom(b,c).

pushdown(B,C) | npushdown(B,C) :- bottom(B), time0(T), box(B,T), pushable_bottom(B,C).


box(B,T) :- pushdown(_,B), time1(T).
box(B,T) :- boxinit(B,T).
boxinit(b,0).


good_pushlocation(c).

"""
