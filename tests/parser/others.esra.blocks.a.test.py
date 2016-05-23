input = """
% Date: Sun, 13 Sep 1998 18:43:04 -0500 (CDT)
% From: Esra Erdem <esra@cs.utexas.edu>
% To: Gerald Pfeifer <pfeifer@dbai.tuwien.ac.at>
% Message-ID: <Pine.GSO.3.96.980913172002.14338A-100000@katie-kaboom.cs.utexas.edu>

% blocks world domain
%    fluents: on(Block,Location)
%    actions: move(Block,Location)

% blocks are b0,b1,...,bn
% location may be any block or table

% effect of moving a block

on(B,L,T1) :- block(B), location(L), move(B,L,T), next(T,T1).

% a block can be moved only when it's clear and the goal location is clear

:- move(B,L,T),on(B1,B,T).
:- block(B1),move(B,B1,T),on(B2,B1,T).

% wherever a block is, it's not anywhere else

-on(B,L1,T) :- on(B,L,T), location(L1), not eq(L,L1).

% a block is never on top of itself

:- block(B),time(T),on(B,B,T).

% no actions are executed at last time

:- move(B,L,T), not nlasttime(T).

% no concurrency

:- move(B,L,T),move(B1,L1,T),not eq(B,B1).
:- move(B,L,T),move(B1,L1,T),not eq(L,L1).

% inertia

on(B,L,T1) :- on(B,L,T),next(T,T1),not -on(B,L,T1).
-on(B,L,T1) :- -on(B,L,T),next(T,T1),not on(B,L,T1).

% initial values and actions are exogeneous

on(B,L,0) | -on(B,L,0) :- block(B),location(L).
move(B,L,T) | -move(B,L,T):- block(B),location(L),time(T).

% consistency

:- on(B,L,T),-on(B,L,T).
:- move(B,L,T),-move(B,L,T).

% time(0), time(1), ... , time(k)
true.
time(0) :- true.
time(T1) :- next(T,T1).

% include -N=k as an option 
%time(T) :- #int(T).

nlasttime(T) :- next(T,T1).

location(L) :- block(L).
location(table) :- true.

eq(L,L) :- location(L).

% auxiliary predicates

block(b0).
block(b1).
block(b2).

next(0,1).
next(1,2).
next(2,3).

% planning problem

% sussman anomaly
% initial: 1 0/2 (i.e., b1 and b2 are on the table, and b2 is on b0) 
% goal: 0/1/2    (i.e., b0 is on the table, b1 is on b0, and b2 is on b1)

on(b1, table, 0) :- true.
on(b2, b0, 0) :- true.
on(b0, table, 0) :- true.

on(b2, b1, 3)? %, on(b1, b0, 3), on(b0, table, 3) ?

"""
output = """
% Date: Sun, 13 Sep 1998 18:43:04 -0500 (CDT)
% From: Esra Erdem <esra@cs.utexas.edu>
% To: Gerald Pfeifer <pfeifer@dbai.tuwien.ac.at>
% Message-ID: <Pine.GSO.3.96.980913172002.14338A-100000@katie-kaboom.cs.utexas.edu>

% blocks world domain
%    fluents: on(Block,Location)
%    actions: move(Block,Location)

% blocks are b0,b1,...,bn
% location may be any block or table

% effect of moving a block

on(B,L,T1) :- block(B), location(L), move(B,L,T), next(T,T1).

% a block can be moved only when it's clear and the goal location is clear

:- move(B,L,T),on(B1,B,T).
:- block(B1),move(B,B1,T),on(B2,B1,T).

% wherever a block is, it's not anywhere else

-on(B,L1,T) :- on(B,L,T), location(L1), not eq(L,L1).

% a block is never on top of itself

:- block(B),time(T),on(B,B,T).

% no actions are executed at last time

:- move(B,L,T), not nlasttime(T).

% no concurrency

:- move(B,L,T),move(B1,L1,T),not eq(B,B1).
:- move(B,L,T),move(B1,L1,T),not eq(L,L1).

% inertia

on(B,L,T1) :- on(B,L,T),next(T,T1),not -on(B,L,T1).
-on(B,L,T1) :- -on(B,L,T),next(T,T1),not on(B,L,T1).

% initial values and actions are exogeneous

on(B,L,0) | -on(B,L,0) :- block(B),location(L).
move(B,L,T) | -move(B,L,T):- block(B),location(L),time(T).

% consistency

:- on(B,L,T),-on(B,L,T).
:- move(B,L,T),-move(B,L,T).

% time(0), time(1), ... , time(k)
true.
time(0) :- true.
time(T1) :- next(T,T1).

% include -N=k as an option 
%time(T) :- #int(T).

nlasttime(T) :- next(T,T1).

location(L) :- block(L).
location(table) :- true.

eq(L,L) :- location(L).

% auxiliary predicates

block(b0).
block(b1).
block(b2).

next(0,1).
next(1,2).
next(2,3).

% planning problem

% sussman anomaly
% initial: 1 0/2 (i.e., b1 and b2 are on the table, and b2 is on b0) 
% goal: 0/1/2    (i.e., b0 is on the table, b1 is on b0, and b2 is on b1)

on(b1, table, 0) :- true.
on(b2, b0, 0) :- true.
on(b0, table, 0) :- true.

on(b2, b1, 3)? %, on(b1, b0, 3), on(b0, table, 3) ?

"""
