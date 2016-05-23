input = """
% Date: Wed, 15 Jul 1998 15:11:06 -0500 (CDT)
% From: Esra Erdem <esra@cs.utexas.edu>
% To: Gerald Pfeifer <pfeifer@dbai.tuwien.ac.at>
% Subject: Re: experimentation

up(L,T1) :- latch(L), next(T,T1), up(L,T), not nup(L,T1).
nup(L,T1) :- latch(L), next(T,T1), nup(L,T), not up(L,T1).

open(T1) :- next(T,T1), open(T), not nopen(T1).
nopen(T1) :- next(T,T1), nopen(T), not open(T1).

up(L,T1) :- latch(L), next(T,T1), toggle(L,T), nup(L,T).
nup(L,T1) :- latch(L), next(T,T1), toggle(L,T), up(L,T).

open(T) :- up(l1,T), up(l2,T).

up(L,0) :-  latch(L), not nup(L,0).
nup(L,0) :-  latch(L), not up(L,0).

open(0) :- not nopen(0).
nopen(0) :- not open(0).

toggle(L,T) :- latch(L), time(T), not last(T), not ntoggle(L,T).
ntoggle(L,T) :- latch(L), time(T), not last(T), not toggle(L,T).

latch(l1).
latch(l2).

time(0).
time(1).
time(2).

last(2).

next(0,1).
next(1,2).

% find all stable models containing open(2) but not any of the following:
% up(l1,0), up(l2,0), open(0), up(l1,2), up(l2,2)

% compute all {open(2), not up(l1,0), not up(l2,0), not open(0), not
% up(l1,2), not up(l2,2)}

open(2)? %, not up(l1,0), not up(l2,0), not open(0), not up(l1,2), not up(l2,2)?
"""
output = """
% Date: Wed, 15 Jul 1998 15:11:06 -0500 (CDT)
% From: Esra Erdem <esra@cs.utexas.edu>
% To: Gerald Pfeifer <pfeifer@dbai.tuwien.ac.at>
% Subject: Re: experimentation

up(L,T1) :- latch(L), next(T,T1), up(L,T), not nup(L,T1).
nup(L,T1) :- latch(L), next(T,T1), nup(L,T), not up(L,T1).

open(T1) :- next(T,T1), open(T), not nopen(T1).
nopen(T1) :- next(T,T1), nopen(T), not open(T1).

up(L,T1) :- latch(L), next(T,T1), toggle(L,T), nup(L,T).
nup(L,T1) :- latch(L), next(T,T1), toggle(L,T), up(L,T).

open(T) :- up(l1,T), up(l2,T).

up(L,0) :-  latch(L), not nup(L,0).
nup(L,0) :-  latch(L), not up(L,0).

open(0) :- not nopen(0).
nopen(0) :- not open(0).

toggle(L,T) :- latch(L), time(T), not last(T), not ntoggle(L,T).
ntoggle(L,T) :- latch(L), time(T), not last(T), not toggle(L,T).

latch(l1).
latch(l2).

time(0).
time(1).
time(2).

last(2).

next(0,1).
next(1,2).

% find all stable models containing open(2) but not any of the following:
% up(l1,0), up(l2,0), open(0), up(l1,2), up(l2,2)

% compute all {open(2), not up(l1,0), not up(l2,0), not open(0), not
% up(l1,2), not up(l2,2)}

open(2)? %, not up(l1,0), not up(l2,0), not open(0), not up(l1,2), not up(l2,2)?
"""
