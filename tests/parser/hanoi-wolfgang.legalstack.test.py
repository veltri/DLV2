input = """
% Originally called hanoi-greco-inspired2.dl.
%
% Employ the notion of legal stacks, which carry information of the top
% element and the rest of the stack and addition to the entires stack itself.

true.
number(15).

largest_disc(4).

%------ Initial state

q(0,4321,0,0) :- true.

% ------ Goal state

query(X,Y,Z) :- number(J), q(J,X,Y,Z).



% ------ all discs involved ------

disc(X) :- largest_disc(X).
disc(X) :- disc(Y), X != 0. % #succ(X,Y), X != 0.

% ------ legal non-empty stacks, their top element and the rest stack ------

legalstack_top_rest(D,D,0) :- disc(D).
legalstack_top_rest(S,T,B) :- legalstack_top_rest(B,T1,R1), disc(T), T < T1, AUX = B * 10, S = AUX + T.

% ------ possible moves ------

% From stack one to stack two.

m(I1,S1,S2,L3) :-  q(I,L1,L2,L3),
                   number(J), I < J, %#succ(I,I1),
                   legalstack_top_rest(L1,X,S1),
                   legalstack_top_rest(S2,X,L2).

% From stack one to stack three.

m(I1,S1,L2,S3) :-  q(I,L1,L2,L3),
                   number(J), I < J, %#succ(I,I1),
                   legalstack_top_rest(L1,X,S1),
                   legalstack_top_rest(S3,X,L3).

% From stack two to stack one.

m(I1,S1,S2,L3) :-  q(I,L1,L2,L3),
                   number(J), I < J, %#succ(I,I1),
                   legalstack_top_rest(L2,X,S2),
                   legalstack_top_rest(S1,X,L1).

% From stack two to stack three.

m(I1,L1,S2,S3) :-  q(I,L1,L2,L3),
                   number(J), I < J, %#succ(I,I1),
                   legalstack_top_rest(L2,X,S2),
                   legalstack_top_rest(S3,X,L3).

% From stack three to stack one.

m(I1,S1,L2,S3) :-  q(I,L1,L2,L3),
                   number(J), I < J, %#succ(I,I1),
                   legalstack_top_rest(L3,X,S3),
                   legalstack_top_rest(S1,X,L1).

% From stack three to stack two.

m(I1,L1,S2,S3) :-  q(I,L1,L2,L3),
                   number(J), I < J, %#succ(I,I1),
                   legalstack_top_rest(L3,X,S3),
                   legalstack_top_rest(S2,X,L2).

q(I,A1,A2,A3) | noq(I,A1,A2,A3) :- m(I,A1,A2,A3).

%------ Vincolo: Una configurazione ad ogni step ------

:- q(I,L1,L2,L3), q(I,M1,M2,M3), L1 != M1.
:- q(I,L1,L2,L3), q(I,M1,M2,M3), L2 != M2.
:- q(I,L1,L2,L3), q(I,M1,M2,M3), L3 != M3.

query(0,0,4321)?"""
output = """
% Originally called hanoi-greco-inspired2.dl.
%
% Employ the notion of legal stacks, which carry information of the top
% element and the rest of the stack and addition to the entires stack itself.

true.
number(15).

largest_disc(4).

%------ Initial state

q(0,4321,0,0) :- true.

% ------ Goal state

query(X,Y,Z) :- number(J), q(J,X,Y,Z).



% ------ all discs involved ------

disc(X) :- largest_disc(X).
disc(X) :- disc(Y), X != 0. % #succ(X,Y), X != 0.

% ------ legal non-empty stacks, their top element and the rest stack ------

legalstack_top_rest(D,D,0) :- disc(D).
legalstack_top_rest(S,T,B) :- legalstack_top_rest(B,T1,R1), disc(T), T < T1, AUX = B * 10, S = AUX + T.

% ------ possible moves ------

% From stack one to stack two.

m(I1,S1,S2,L3) :-  q(I,L1,L2,L3),
                   number(J), I < J, %#succ(I,I1),
                   legalstack_top_rest(L1,X,S1),
                   legalstack_top_rest(S2,X,L2).

% From stack one to stack three.

m(I1,S1,L2,S3) :-  q(I,L1,L2,L3),
                   number(J), I < J, %#succ(I,I1),
                   legalstack_top_rest(L1,X,S1),
                   legalstack_top_rest(S3,X,L3).

% From stack two to stack one.

m(I1,S1,S2,L3) :-  q(I,L1,L2,L3),
                   number(J), I < J, %#succ(I,I1),
                   legalstack_top_rest(L2,X,S2),
                   legalstack_top_rest(S1,X,L1).

% From stack two to stack three.

m(I1,L1,S2,S3) :-  q(I,L1,L2,L3),
                   number(J), I < J, %#succ(I,I1),
                   legalstack_top_rest(L2,X,S2),
                   legalstack_top_rest(S3,X,L3).

% From stack three to stack one.

m(I1,S1,L2,S3) :-  q(I,L1,L2,L3),
                   number(J), I < J, %#succ(I,I1),
                   legalstack_top_rest(L3,X,S3),
                   legalstack_top_rest(S1,X,L1).

% From stack three to stack two.

m(I1,L1,S2,S3) :-  q(I,L1,L2,L3),
                   number(J), I < J, %#succ(I,I1),
                   legalstack_top_rest(L3,X,S3),
                   legalstack_top_rest(S2,X,L2).

q(I,A1,A2,A3) | noq(I,A1,A2,A3) :- m(I,A1,A2,A3).

%------ Vincolo: Una configurazione ad ogni step ------

:- q(I,L1,L2,L3), q(I,M1,M2,M3), L1 != M1.
:- q(I,L1,L2,L3), q(I,M1,M2,M3), L2 != M2.
:- q(I,L1,L2,L3), q(I,M1,M2,M3), L3 != M3.

query(0,0,4321)?"""
