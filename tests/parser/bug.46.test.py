input = """
% Reported by Axel Polleres to trigger a bug with -OR.

true.
%actiontime(T) :- T < #maxint, #int(T).
location(t) :- true.
location(B) :- block(B).

% blocksC2.dl without free variables
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Blocks world domain description in C
% Elementary Actions: move(B,L) for all blocks B and locations L
% Fluents: on(B,L) for all blocks B and locations L

% effect of moving a block

% move(B,L) causes on(B,L)  (for all blocks B and locations L)
on(B,L,T1) :- move(B,L,T).%, #succ(T,T1).

% move(B,L) causes -on(B,L1) if on(B,L1)
-on(B,L,T1) :- move1(B,T), on(B,L,T).%, #succ(T,T1).


% a block can be moved only when it's clear
% nonexecutable move(B,L) if on(B1,B) (for all blocks B,B1 and locations L)
% :- move(B,L,T), on(B1,B,T).
% pushed into guess

% any two blocks cannot be on the same block at the same time.         
% that means a block cannot be moved to an occupied block:
% nonexecutable move(B,B1) if on(B2,B1) & block(B1)
% :- move(B,B1,T), on(B2,B1,T), block(B1).
% pushed into guess using the following auxiliary predicate:
onblock(B,T) :- on(_,B,T), block(B).

% wherever a block is, it's not anywhere else                          
% caused -on(B,L1) if on(B,L) (for all blocks B, and locations L,L1
%                                where -(L=L1))                         (2)
% assuming a complete initial description this can be skipped !!!



% a block is never on top of itself 
% that means it cannot be moved on top of itself:
% nonexecutable move(B,B). 
% :- move(B,B,T).
% pushed into guess.

% no concurrency
% nonexecutable (move(B,L), move(B1,L1)) if (B!=B1)
move1(B,T) :- move(B,_,T).
move2(L,T) :- move(_,L,T).
:- move1(B,T), move1(B1,T), B!=B1.
% nonexecutable (move(B,L), move(B1,L1)) if (L!=L1)
:- move2(L,T), move2(L1,T), L!=L1.


% inertia
% inertial on
on(B,L,T1) :- on(B,L,T), not -on(B,L,T1).%, #succ(T,T1).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

move(B,L,T) | -move(B,L,T) :- block(B), location(L), actiontime(T),
			  not onblock(L,T), not onblock(B,T), B!=L.



block(b1).
block(b2).
block(b3).
block(b4).
block(b5).

on(b5,t,0) :- true.
on(b3,t,0) :- true.
on(b2,b5,0) :- true.
on(b4,b3,0) :- true.
on(b1,b4,0) :- true.

%on(b1,t,#maxint),on(b2,b1,#maxint), on(b3,b2,#maxint),on(b4,b3,#maxint), on(b5,b4,#maxint)?

on(b5,b4)?

"""
output = """
% Reported by Axel Polleres to trigger a bug with -OR.

true.
%actiontime(T) :- T < #maxint, #int(T).
location(t) :- true.
location(B) :- block(B).

% blocksC2.dl without free variables
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Blocks world domain description in C
% Elementary Actions: move(B,L) for all blocks B and locations L
% Fluents: on(B,L) for all blocks B and locations L

% effect of moving a block

% move(B,L) causes on(B,L)  (for all blocks B and locations L)
on(B,L,T1) :- move(B,L,T).%, #succ(T,T1).

% move(B,L) causes -on(B,L1) if on(B,L1)
-on(B,L,T1) :- move1(B,T), on(B,L,T).%, #succ(T,T1).


% a block can be moved only when it's clear
% nonexecutable move(B,L) if on(B1,B) (for all blocks B,B1 and locations L)
% :- move(B,L,T), on(B1,B,T).
% pushed into guess

% any two blocks cannot be on the same block at the same time.         
% that means a block cannot be moved to an occupied block:
% nonexecutable move(B,B1) if on(B2,B1) & block(B1)
% :- move(B,B1,T), on(B2,B1,T), block(B1).
% pushed into guess using the following auxiliary predicate:
onblock(B,T) :- on(_,B,T), block(B).

% wherever a block is, it's not anywhere else                          
% caused -on(B,L1) if on(B,L) (for all blocks B, and locations L,L1
%                                where -(L=L1))                         (2)
% assuming a complete initial description this can be skipped !!!



% a block is never on top of itself 
% that means it cannot be moved on top of itself:
% nonexecutable move(B,B). 
% :- move(B,B,T).
% pushed into guess.

% no concurrency
% nonexecutable (move(B,L), move(B1,L1)) if (B!=B1)
move1(B,T) :- move(B,_,T).
move2(L,T) :- move(_,L,T).
:- move1(B,T), move1(B1,T), B!=B1.
% nonexecutable (move(B,L), move(B1,L1)) if (L!=L1)
:- move2(L,T), move2(L1,T), L!=L1.


% inertia
% inertial on
on(B,L,T1) :- on(B,L,T), not -on(B,L,T1).%, #succ(T,T1).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

move(B,L,T) | -move(B,L,T) :- block(B), location(L), actiontime(T),
			  not onblock(L,T), not onblock(B,T), B!=L.



block(b1).
block(b2).
block(b3).
block(b4).
block(b5).

on(b5,t,0) :- true.
on(b3,t,0) :- true.
on(b2,b5,0) :- true.
on(b4,b3,0) :- true.
on(b1,b4,0) :- true.

%on(b1,t,#maxint),on(b2,b1,#maxint), on(b3,b2,#maxint),on(b4,b3,#maxint), on(b5,b4,#maxint)?

on(b5,b4)?

"""
