input = """
supp(B) :- on(B,table,0).
supp(B) :- on(B,B1,0), supp(B1).

on(b0,table,0) :- true.
on(b1,b0,0) :- true.

on(B,L,0) | -on(B,L,0) :- block(B), location(L).

true.
location(L) :- block(L).
location(table) :- true.

block(b0).
block(b1).
block(b2).

"""
output = """
supp(B) :- on(B,table,0).
supp(B) :- on(B,B1,0), supp(B1).

on(b0,table,0) :- true.
on(b1,b0,0) :- true.

on(B,L,0) | -on(B,L,0) :- block(B), location(L).

true.
location(L) :- block(L).
location(table) :- true.

block(b0).
block(b1).
block(b2).

"""
