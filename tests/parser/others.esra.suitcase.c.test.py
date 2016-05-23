input = """
% The rules for up/2 have been rewritten to a disjunctive rule 
% and constraints, yielding a guess-and-check-like program.

% Lin's suitcase domain:
%   fluents: up(L), open
%   actions: toggle(L)
%   initially: the latches (i.e., l1 and l2) are down and the suitcase is
%              closed
%   goal: the latches are down and the suitcase is open

%   classical negation of open, up, and toggle  are  represented by nopen,
%      nup, and ntoggle  respectively.

% action description (in C):
%   inertial up(L), nup(L), open, nopen
%   caused up(L) after toggle(L) /\ nup(L)
%   caused nup(L) after toggle(L) /\ up(L)
%   caused open if up(l1) /\ up(l2)

% transform into a logic program

% the new guess-and-check stuff

up(L,T) | -up(L,T) :- latch(L), time(T).

:- up(L,T), next(T,T1), up(L,T1), toggle(L,T).
:- -up(L,T), next(T,T1), -up(L,T1), toggle(L,T).
:- up(L,T), next(T,T1), -up(L,T1), -toggle(L,T).
:- -up(L,T), next(T,T1), up(L,T1), -toggle(L,T).

% the old rules

%up(L,T1) :- latch(L), next(T,T1), up(L,T), not -up(L,T1).
%-up(L,T1) :- latch(L), next(T,T1), -up(L,T), not up(L,T1).
%up(L,T1) :- latch(L), next(T,T1), toggle(L,T), -up(L,T).
%-up(L,T1) :- latch(L), next(T,T1), toggle(L,T), up(L,T).

open(T1) :- next(T,T1), open(T), not -open(T1).
-open(T1) :- next(T,T1), -open(T), not open(T1).

open(T) :- up(l1,T), up(l2,T).

% The following two rules are subsumed by the new disjunctive rule.

%up(L,0) :-  latch(L), not -up(L,0).
%-up(L,0) :-  latch(L), not up(L,0).

%up(L,0) | -up(L,0) :- latch(L).

% open(0) :- not -open(0).
% -open(0) :- not open(0).

open(0) | -open(0).

%toggle(L,T) :- latch(L), time(T), not last(T), not -toggle(L,T).
%-toggle(L,T) :- latch(L), time(T), not last(T), not toggle(L,T).

toggle(L,T) | -toggle(L,T) :- latch(L), time(T), not last(T).

latch(l1). 
latch(l2).

time(0).
time(1).
time(2).

last(2).

next(0,1).
next(1,2).

:- up(l1,0).
:- up(l2,0).
:- open(0).
:- not open(2).
:- up(l1,2).
:- up(l2,2).

% OR in a more intuitive way, the above 6 ICs can be written as:
% goal :- open(2), not up(l1,0), not up(l2,0), not open(0), not up(l1,2),
%         not up(l2,2).
% :- not goal.


% OR they can be written as a query (used with brave reasoning):
% open(2), not up(l1,0), not up(l2,0), not open(0), not up(l1,2), not
% up(l2,2)?
"""
output = """
% The rules for up/2 have been rewritten to a disjunctive rule 
% and constraints, yielding a guess-and-check-like program.

% Lin's suitcase domain:
%   fluents: up(L), open
%   actions: toggle(L)
%   initially: the latches (i.e., l1 and l2) are down and the suitcase is
%              closed
%   goal: the latches are down and the suitcase is open

%   classical negation of open, up, and toggle  are  represented by nopen,
%      nup, and ntoggle  respectively.

% action description (in C):
%   inertial up(L), nup(L), open, nopen
%   caused up(L) after toggle(L) /\ nup(L)
%   caused nup(L) after toggle(L) /\ up(L)
%   caused open if up(l1) /\ up(l2)

% transform into a logic program

% the new guess-and-check stuff

up(L,T) | -up(L,T) :- latch(L), time(T).

:- up(L,T), next(T,T1), up(L,T1), toggle(L,T).
:- -up(L,T), next(T,T1), -up(L,T1), toggle(L,T).
:- up(L,T), next(T,T1), -up(L,T1), -toggle(L,T).
:- -up(L,T), next(T,T1), up(L,T1), -toggle(L,T).

% the old rules

%up(L,T1) :- latch(L), next(T,T1), up(L,T), not -up(L,T1).
%-up(L,T1) :- latch(L), next(T,T1), -up(L,T), not up(L,T1).
%up(L,T1) :- latch(L), next(T,T1), toggle(L,T), -up(L,T).
%-up(L,T1) :- latch(L), next(T,T1), toggle(L,T), up(L,T).

open(T1) :- next(T,T1), open(T), not -open(T1).
-open(T1) :- next(T,T1), -open(T), not open(T1).

open(T) :- up(l1,T), up(l2,T).

% The following two rules are subsumed by the new disjunctive rule.

%up(L,0) :-  latch(L), not -up(L,0).
%-up(L,0) :-  latch(L), not up(L,0).

%up(L,0) | -up(L,0) :- latch(L).

% open(0) :- not -open(0).
% -open(0) :- not open(0).

open(0) | -open(0).

%toggle(L,T) :- latch(L), time(T), not last(T), not -toggle(L,T).
%-toggle(L,T) :- latch(L), time(T), not last(T), not toggle(L,T).

toggle(L,T) | -toggle(L,T) :- latch(L), time(T), not last(T).

latch(l1). 
latch(l2).

time(0).
time(1).
time(2).

last(2).

next(0,1).
next(1,2).

:- up(l1,0).
:- up(l2,0).
:- open(0).
:- not open(2).
:- up(l1,2).
:- up(l2,2).

% OR in a more intuitive way, the above 6 ICs can be written as:
% goal :- open(2), not up(l1,0), not up(l2,0), not open(0), not up(l1,2),
%         not up(l2,2).
% :- not goal.


% OR they can be written as a query (used with brave reasoning):
% open(2), not up(l1,0), not up(l2,0), not open(0), not up(l1,2), not
% up(l2,2)?
"""
