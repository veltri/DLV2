input = """
% Originally known as conditionalPlan. By Francesco Scarcello. 
%
%%% GOAL %%%

%          b
%          c
%   a      d
%--------------

% For the conditional planning is convenient to give notGoal,
% i.e., a representation of the final states that do not satisfy the goal.
% This is very easy, because we have defined the predicate notOn.
notGoal :- notOn(d,table,T), lastTime(T).
notGoal :- notOn(c,d,T), lastTime(T).
notGoal :- notOn(b,c,T), lastTime(T).
notGoal :- notOn(a,table,T), lastTime(T).


%%% INITIAL STATE MODULE %%%

%%% PARTIAL INITIAL STATE %%%
% Note that we do not know anything about the block  a
on(d,c,0):-true.
on(c,b,0):-true.


% guess for completions
on(B,L,0) | notOn(B,L,0) :- block(B), location(L).

 :- block(B), unsupported(B,0).
 :- block(B), on(B2,B,0), on(B1,B,0), B1!=B2.
 :- block(B), on(B,B2,0), on(B,B1,0), B1!=B2.
 :- on(B,L,0), notOn(B,L,0).
 :- on(B,B,0).


%%% GUESS FOR ACTIONS %%%

% guess for actions
move(B,L,T) | notMove(B,L,T) :- block(B), location(L), time(T), B!=L.

% no actions moving a block on itself
notMove(B,B,T) :- block(B), time(T).

% no actions are executed at last time
illegal :- move(B,L,T), lastTime(T).

% no concurrency
illegal :- move(B,L,T), move(B1,L1,T), B < B1.
illegal :- move(B,L,T), move(B1,L1,T), L < L1.


%%% TRANSITION FUNCTION MODULE %%%

% effect of moving a block
on(B,L,T1) :- block(B), location(L), move(B,L,T), next(T,T1).

% a block can be moved only when it's clear
illegal :- move(B,L,T), on(B1,B,T).

% wherever a block is, it's not anywhere else
notOn(B,L1,T) :- on(B,L,T), location(L1), L!=L1.

% inertia
on(B,L,T1) :- on(B,L,T), next(T,T1), notMoved(B,T).

% State constraints
illegal :- block(B), unsupported(B,T).
illegal :- block(B), on(B2,B,T), on(B1,B,T), B1!=B2.
illegal :- block(B), on(B,B2,T), on(B,B1,T), B1!=B2.
illegal :- on(B,L,T), notOn(B,L,T).
illegal :- on(B,B,T).



%%% SATURATION %%

checkedState :- notGoal.
checkedState :- illegal.

% saturation
move(B,L,T)    :- checkedState, time(T), block(B), location(L).
notMove(B,L,T) :- checkedState, time(T), block(B), location(L).
notOn(B,L,T)   :- checkedState, time(T), block(B), location(L), T!=0.

% constraint
:- not checkedState.


%%% BACKGROUND KNOWLEDGE %%%

block(a). block(b). block(c). block(d).
location(L) :- block(L).
location(table):- true.

firstBlock(a). lastBlock(d).
nextBlock(a,b). nextBlock(b,c). nextBlock(c,d).

% include -N=k as an option
%time(T) :- #int(T).
%lastTime(#maxint).
%next(X,Y) :- #succ(X,Y), #int(X).


%%% USEFUL PREDICATES %%%
true.

% Check whether block B is unsupported
unsupported(B,T) :- supportedBy(B,B,T).
unsupported(B,T) :- dangling(B,MAX,T), lastBlock(MAX).

supportedBy(B,L,T) :- on(B,L,T).
supportedBy(B,L,T) :- supportedBy(B,B1,T), on(B1,L,T).

dangling(B,B1,T):- firstBlock(B1), notOn(B,B1,T), notOn(B,table,T).
dangling(B,B1,T):- dangling(B,B2,T), nextBlock(B2,B1), notOn(B,B1,T).

% check whether a block is not moved at a given instant
notMoved(B,T) :- notMovedUntil(B,T,MAX), lastBlock(MAX).

notMovedUntil(B,T,B1) :- notMove(B,table,T), notMove(B,B1,T), firstBlock(B1).
notMovedUntil(B,T,B2) :- notMovedUntil(B,T,B1), nextBlock(B1,B2),
                         notMove(B,B2,T).
"""
output = """
% Originally known as conditionalPlan. By Francesco Scarcello. 
%
%%% GOAL %%%

%          b
%          c
%   a      d
%--------------

% For the conditional planning is convenient to give notGoal,
% i.e., a representation of the final states that do not satisfy the goal.
% This is very easy, because we have defined the predicate notOn.
notGoal :- notOn(d,table,T), lastTime(T).
notGoal :- notOn(c,d,T), lastTime(T).
notGoal :- notOn(b,c,T), lastTime(T).
notGoal :- notOn(a,table,T), lastTime(T).


%%% INITIAL STATE MODULE %%%

%%% PARTIAL INITIAL STATE %%%
% Note that we do not know anything about the block  a
on(d,c,0):-true.
on(c,b,0):-true.


% guess for completions
on(B,L,0) | notOn(B,L,0) :- block(B), location(L).

 :- block(B), unsupported(B,0).
 :- block(B), on(B2,B,0), on(B1,B,0), B1!=B2.
 :- block(B), on(B,B2,0), on(B,B1,0), B1!=B2.
 :- on(B,L,0), notOn(B,L,0).
 :- on(B,B,0).


%%% GUESS FOR ACTIONS %%%

% guess for actions
move(B,L,T) | notMove(B,L,T) :- block(B), location(L), time(T), B!=L.

% no actions moving a block on itself
notMove(B,B,T) :- block(B), time(T).

% no actions are executed at last time
illegal :- move(B,L,T), lastTime(T).

% no concurrency
illegal :- move(B,L,T), move(B1,L1,T), B < B1.
illegal :- move(B,L,T), move(B1,L1,T), L < L1.


%%% TRANSITION FUNCTION MODULE %%%

% effect of moving a block
on(B,L,T1) :- block(B), location(L), move(B,L,T), next(T,T1).

% a block can be moved only when it's clear
illegal :- move(B,L,T), on(B1,B,T).

% wherever a block is, it's not anywhere else
notOn(B,L1,T) :- on(B,L,T), location(L1), L!=L1.

% inertia
on(B,L,T1) :- on(B,L,T), next(T,T1), notMoved(B,T).

% State constraints
illegal :- block(B), unsupported(B,T).
illegal :- block(B), on(B2,B,T), on(B1,B,T), B1!=B2.
illegal :- block(B), on(B,B2,T), on(B,B1,T), B1!=B2.
illegal :- on(B,L,T), notOn(B,L,T).
illegal :- on(B,B,T).



%%% SATURATION %%

checkedState :- notGoal.
checkedState :- illegal.

% saturation
move(B,L,T)    :- checkedState, time(T), block(B), location(L).
notMove(B,L,T) :- checkedState, time(T), block(B), location(L).
notOn(B,L,T)   :- checkedState, time(T), block(B), location(L), T!=0.

% constraint
:- not checkedState.


%%% BACKGROUND KNOWLEDGE %%%

block(a). block(b). block(c). block(d).
location(L) :- block(L).
location(table):- true.

firstBlock(a). lastBlock(d).
nextBlock(a,b). nextBlock(b,c). nextBlock(c,d).

% include -N=k as an option
%time(T) :- #int(T).
%lastTime(#maxint).
%next(X,Y) :- #succ(X,Y), #int(X).


%%% USEFUL PREDICATES %%%
true.

% Check whether block B is unsupported
unsupported(B,T) :- supportedBy(B,B,T).
unsupported(B,T) :- dangling(B,MAX,T), lastBlock(MAX).

supportedBy(B,L,T) :- on(B,L,T).
supportedBy(B,L,T) :- supportedBy(B,B1,T), on(B1,L,T).

dangling(B,B1,T):- firstBlock(B1), notOn(B,B1,T), notOn(B,table,T).
dangling(B,B1,T):- dangling(B,B2,T), nextBlock(B2,B1), notOn(B,B1,T).

% check whether a block is not moved at a given instant
notMoved(B,T) :- notMovedUntil(B,T,MAX), lastBlock(MAX).

notMovedUntil(B,T,B1) :- notMove(B,table,T), notMove(B,B1,T), firstBlock(B1).
notMovedUntil(B,T,B2) :- notMovedUntil(B,T,B1), nextBlock(B1,B2),
                         notMove(B,B2,T).
"""
