input = """
on(B,L,T1) :- move(B,L,T), T1=T+1.
on(B,L,T1) :- on(B,L,T), T1=T+1, not moved(B,T).
moved(B,T) :- move(B,_,T).
:- on(B,L,T), on(B,L1,T), L!=L1.
:- on(B1,B,T), on(B2,B,T),B2!=B1, block(B).
:- on(B,B,T).
:- move(B,B1,T), move(B1,L,T).
:- move(B,L,T), on(B1,B,T), B!=B1.

on(d,table,0).
on(b,table,0).
on(f,table,0).
on(a,b,0).
on(e,f,0).
on(c,e,0).
"""
output = """
on(B,L,T1) :- move(B,L,T), T1=T+1.
on(B,L,T1) :- on(B,L,T), T1=T+1, not moved(B,T).
moved(B,T) :- move(B,_,T).
:- on(B,L,T), on(B,L1,T), L!=L1.
:- on(B1,B,T), on(B2,B,T),B2!=B1, block(B).
:- on(B,B,T).
:- move(B,B1,T), move(B1,L,T).
:- move(B,L,T), on(B1,B,T), B!=B1.

on(d,table,0).
on(b,table,0).
on(f,table,0).
on(a,b,0).
on(e,f,0).
on(c,e,0).
"""
