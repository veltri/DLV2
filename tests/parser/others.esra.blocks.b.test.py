input = """
% Date: Wed, 14 Oct 1998 10:22:30 -0500 (CDT)
% From: Esra Erdem <esra@cs.utexas.edu>
% To: Gerald Pfeifer <pfeifer@dbai.tuwien.ac.at>
% Message-ID: <Pine.LNX.3.96.981014101559.22229A-100000@pillbox.cs.utexas.edu>
%
% This is the version for smodels, where I have replaced the compute{} statement
% by a query and resolved two EDB/IDB problems by adding a rule of the form 
% sth :- true. [Gerald, 14.10.1998]

% non(B,L,T) represents the classical negation of on(B,L,T), and similarly
% for the other predicates with mysterious names beginning with n.

% effect of moving a block

true.

on(B,L,T1) :- block(B),location(L),move(B,L,T),next(T,T1).

% a block can be moved only when it's clear and the goal location is clear

false :- move(B,L,T),on(B1,B,T).
false :- block(B1),move(B,B1,T),on(B2,B1,T).

% wherever a block is, it's not anywhere else

non_(B,L1,T) :- on(B,L,T),location(L1),not eq(L,L1).

% a block is never on top of itself

false :- block(B),time(T),on(B,B,T).

% no actions are executed at last time

false :- move(B,L,T), not nlasttime(T).

% no concurrency

false :- move(B,L,T),move(B1,L1,T),not eq(B,B1).
false :- move(B,L,T),move(B1,L1,T),not eq(L,L1).

% inertia

on(B,L,T1) :- on(B,L,T),not non_(B,L,T1),next(T,T1).
non_(B,L,T1) :- non_(B,L,T),not on(B,L,T1),next(T,T1).

% initial values and actions are exogeneous

on(B,L,0) :- block(B),location(L),not non_(B,L,0).
non_(B,L,0) :- block(B),location(L),not on(B,L,0).

move(B,L,T) :- block(B),location(L),time(T), not nmove(B,L,T).
nmove(B,L,T) :- block(B),location(L),time(T), not move(B,L,T).

% consistency

false :- on(B,L,T),non_(B,L,T).
false :- move(B,L,T),nmove(B,L,T).

% auxiliary predicates

block(b0). block(b1). block(b2).

next(0,1). next(1,2). next(2,3).

time(0) :- true.
time(T1) :- next(T,T1).

nlasttime(T) :- next(T,T1).

location(L) :- block(L).
location(table) :- true.

eq(L,L) :- location(L).

% planning problem

% compute 1 {not false,

% sussman anomaly

% on(b1, table, 0), on(b2,b0, 0), on(b0, table, 0),
% on(b1, b0, 3), on(b2, b1, 3), on(b0, table, 3)
% }

on(b1, table, 0) ? %not false, on(b1, table, 0), on(b2,b0, 0), on(b0, table, 0), on(b1, b0, 3), on(b2, b1, 3), on(b0, table, 3)?

"""
output = """
% Date: Wed, 14 Oct 1998 10:22:30 -0500 (CDT)
% From: Esra Erdem <esra@cs.utexas.edu>
% To: Gerald Pfeifer <pfeifer@dbai.tuwien.ac.at>
% Message-ID: <Pine.LNX.3.96.981014101559.22229A-100000@pillbox.cs.utexas.edu>
%
% This is the version for smodels, where I have replaced the compute{} statement
% by a query and resolved two EDB/IDB problems by adding a rule of the form 
% sth :- true. [Gerald, 14.10.1998]

% non(B,L,T) represents the classical negation of on(B,L,T), and similarly
% for the other predicates with mysterious names beginning with n.

% effect of moving a block

true.

on(B,L,T1) :- block(B),location(L),move(B,L,T),next(T,T1).

% a block can be moved only when it's clear and the goal location is clear

false :- move(B,L,T),on(B1,B,T).
false :- block(B1),move(B,B1,T),on(B2,B1,T).

% wherever a block is, it's not anywhere else

non_(B,L1,T) :- on(B,L,T),location(L1),not eq(L,L1).

% a block is never on top of itself

false :- block(B),time(T),on(B,B,T).

% no actions are executed at last time

false :- move(B,L,T), not nlasttime(T).

% no concurrency

false :- move(B,L,T),move(B1,L1,T),not eq(B,B1).
false :- move(B,L,T),move(B1,L1,T),not eq(L,L1).

% inertia

on(B,L,T1) :- on(B,L,T),not non_(B,L,T1),next(T,T1).
non_(B,L,T1) :- non_(B,L,T),not on(B,L,T1),next(T,T1).

% initial values and actions are exogeneous

on(B,L,0) :- block(B),location(L),not non_(B,L,0).
non_(B,L,0) :- block(B),location(L),not on(B,L,0).

move(B,L,T) :- block(B),location(L),time(T), not nmove(B,L,T).
nmove(B,L,T) :- block(B),location(L),time(T), not move(B,L,T).

% consistency

false :- on(B,L,T),non_(B,L,T).
false :- move(B,L,T),nmove(B,L,T).

% auxiliary predicates

block(b0). block(b1). block(b2).

next(0,1). next(1,2). next(2,3).

time(0) :- true.
time(T1) :- next(T,T1).

nlasttime(T) :- next(T,T1).

location(L) :- block(L).
location(table) :- true.

eq(L,L) :- location(L).

% planning problem

% compute 1 {not false,

% sussman anomaly

% on(b1, table, 0), on(b2,b0, 0), on(b0, table, 0),
% on(b1, b0, 3), on(b2, b1, 3), on(b0, table, 3)
% }

on(b1, table, 0) ? %not false, on(b1, table, 0), on(b2,b0, 0), on(b0, table, 0), on(b1, b0, 3), on(b2, b1, 3), on(b0, table, 3)?

"""
