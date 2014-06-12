input = """
supp(B,T) :- on(B,table,T).
supp(B,T) :- on(B,B1,T), supp(B1,T), B != B1. 

on(B,L,0) | -on(B,L,0) :- block(B), location(L).

time(0).


true.
location(L) :- block(L).
location(table) :- true.

block(b0).
block(b1).
block(b2).

on(b0,table,0) :- true.
on(b1,b0,0) :- true.

"""
output = """
supp(B,T) :- on(B,table,T).
supp(B,T) :- on(B,B1,T), supp(B1,T), B != B1. 

on(B,L,0) | -on(B,L,0) :- block(B), location(L).

time(0).


true.
location(L) :- block(L).
location(table) :- true.

block(b0).
block(b1).
block(b2).

on(b0,table,0) :- true.
on(b1,b0,0) :- true.

"""
