input = """
% blocks world domain presented to DLV:

% effect of moving a block

on(B,L,T1) :- block(B), location(L), move(B,L,T), next(T,T1).

% a block can be moved only when it's clear 

:- move(B,L,T), on(B1,B,T).

% any two blocks cannot be on the same block at the same time.

:- block(B), on(B2,B,T), on(B1,B,T), not eq(B1,B2).

% wherever a block is, it's not anywhere else

-on(B,L1,T) :- on(B,L,T), location(L1), not eq(L,L1).

% every block is supported by the table

supported(B,T) :- on(B,table,T).
supported(B,T) :- on(B,B1,T), supported(B1,T), not eq(B,B1).
:- block(B), time(T), not supported(B,T).

% no actions are executed at last time

:- move(B,L,T), lasttime(T).

% no concurrency

:- move(B,L,T), move(B1,L1,T), not eq(B,B1).
:- move(B,L,T), move(B1,L1,T), not eq(L,L1).

% inertia

on(B,L,T1) :- on(B,L,T), next(T,T1), not -on(B,L,T1).

% initial values and actions are exogeneous

on(B,L,0) | -on(B,L,0) :- block(B), location(L).
move(B,L,T) | -move(B,L,T):- block(B), location(L), time(T), not
-lasttime(T).

% include -N=k as an option 

%time(T) :- #int(T).

%lasttime(#maxint).

true.
location(L) :- block(L).
location(table) :- true.

eq(L,L) :- location(L).

%next(X,Y) :- #succ(X,Y), #int(X).

"""
output = """
% blocks world domain presented to DLV:

% effect of moving a block

on(B,L,T1) :- block(B), location(L), move(B,L,T), next(T,T1).

% a block can be moved only when it's clear 

:- move(B,L,T), on(B1,B,T).

% any two blocks cannot be on the same block at the same time.

:- block(B), on(B2,B,T), on(B1,B,T), not eq(B1,B2).

% wherever a block is, it's not anywhere else

-on(B,L1,T) :- on(B,L,T), location(L1), not eq(L,L1).

% every block is supported by the table

supported(B,T) :- on(B,table,T).
supported(B,T) :- on(B,B1,T), supported(B1,T), not eq(B,B1).
:- block(B), time(T), not supported(B,T).

% no actions are executed at last time

:- move(B,L,T), lasttime(T).

% no concurrency

:- move(B,L,T), move(B1,L1,T), not eq(B,B1).
:- move(B,L,T), move(B1,L1,T), not eq(L,L1).

% inertia

on(B,L,T1) :- on(B,L,T), next(T,T1), not -on(B,L,T1).

% initial values and actions are exogeneous

on(B,L,0) | -on(B,L,0) :- block(B), location(L).
move(B,L,T) | -move(B,L,T):- block(B), location(L), time(T), not
-lasttime(T).

% include -N=k as an option 

%time(T) :- #int(T).

%lasttime(#maxint).

true.
location(L) :- block(L).
location(table) :- true.

eq(L,L) :- location(L).

%next(X,Y) :- #succ(X,Y), #int(X).

"""
