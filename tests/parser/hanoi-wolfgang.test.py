input = """
% Originally called hanoi-greco-inspired1.dl.

true.
number(15).

%------ Stato iniziale: 3 dischi sul primo paletto ------

q(0,4321,0,0) :- true.

%------ Sposta disco dal primo paletto sul secondo o sul terzo ------

m(I1,S1,S2,L3) :-  q(I,L1,L2,L3),
                   I1 = I+1, number(J), I < J, L1 > 0,
                   L1=10/S1, %div(L1,10,S1),
                   mod(L1,10,X),
                   Z = L2*10,
                   S2 = Z + X,
                   allowed(S1),
                   allowed(S2).

m(I1,S1,L2,S3) :-  q(I,L1,L2,L3),
                   I1 = I+1, number(J), I < J, L1 > 0,
                   L1=10/S1, %div(L1,10,S1),
                   mod(L1,10,X),
                   W = L3*10,
                   S3 = W + X,
                   allowed(S1),
                   allowed(S3).

%------ Sposta disco dal secondo paletto sul primo o sul terzo ------

m(I1,S1,S2,L3) :-  q(I,L1,L2,L3),
                   I1 = I+1, number(J), I < J, L2 > 0,
                   L2=10/S2, %div(L2,10,S2),
                   mod(L2,10,X),
                   Z = L1*10,
                   S1 = Z + X,
                   allowed(S1),
                   allowed(S2).

m(I1,L1,S2,S3) :-  q(I,L1,L2,L3),
                   I1 = I+1, number(J), I < J, L2 > 0,
                   L2=10/S2, %div(L2,10,S2),
                   mod(L2,10,X),
                   W = L3*10,
                   S3 = W + X,
                   allowed(S2),
                   allowed(S3).

%------ Sposta disco dal terzo paletto sul primo o sul secondo ------

m(I1,S1,L2,S3) :-  q(I,L1,L2,L3),
                   I1 = I+1, number(J), I < J, L3 > 0,
                   L3=10/S3, %div(L3,10,S3),
                   mod(L3,10,X),
                   Z = L1*10,
                   S1 = Z + X,
                   allowed(S1),
                   allowed(S3).

m(I1,L1,S2,S3) :-  q(I,L1,L2,L3),
                   I1 = I+1, number(J), I < J, L3 > 0,
                   L3=10/S3, %div(L3,10,S3),
                   mod(L3,10,X),
                   W = L2*10,
                   S2 = W + X,
                   allowed(S2),
                   allowed(S3).

q(I,A1,A2,A3) | noq(I,A1,A2,A3) :- m(I,A1,A2,A3).

% ----- the last digit must be smaller than the last but one -----

allowed(L) :- L<10. %#int(L), L<10.
allowed(L) :- L>10, mod(L,10,X), L=10/Y, mod(Y,10,Z), X < Z. %div(L,10,Y), mod(Y,10,Z), X < Z.

%------ Vincolo: Una configurazione ad ogni step ------

%:- q(I,L1,L2,L3), q(J,L1,L2,L3), I != J.
:- q(I,L1,L2,L3), q(I,M1,M2,M3), L1 != M1.
:- q(I,L1,L2,L3), q(I,M1,M2,M3), L2 != M2.
:- q(I,L1,L2,L3), q(I,M1,M2,M3), L3 != M3.
%:- m(I,L1,L2,L3), not have_q(I). 

%have_q(I) :- q(I,_,_,_).

% ------ Query: Tre dischi sul secondo paletto ---

query(X,Y,Z) :- number(J), q(J,X,Y,Z).



% div(4321,10,432).
% div(432,10,43).
% div(431,10,43).
% div(421,10,42).
% div(43,10,4).
% div(42,10,4).
% div(41,10,4).
% div(321,10,32).
% div(312,10,31).
% div(231,10,23).
% div(213,10,21).
% div(132,10,13).
% div(123,10,12).
%div(32,10,3).
%div(31,10,3).
% div(23,10,2).
%div(21,10,2).
% div(13,10,1).
% div(12,10,1).
% div(4,10,0).
% div(3,10,0).
% div(2,10,0).
% div(1,10,0).

mod(4321,10,1).
mod(432,10,2).
mod(431,10,1).
mod(421,10,1).
mod(321,10,1).
mod(43,10,3).
mod(42,10,2).
mod(41,10,1).
% mod(312,10,2).
% mod(231,10,1).
% mod(213,10,3).
% mod(132,10,2).
% mod(123,10,3).
mod(32,10,2).
mod(31,10,1).
% mod(23,10,3).
mod(21,10,1).
% mod(13,10,3).
% mod(12,10,2).
mod(4,10,4).
mod(3,10,3).
mod(2,10,2).
mod(1,10,1).

query(0,0,4321)?
"""
output = """
% Originally called hanoi-greco-inspired1.dl.

true.
number(15).

%------ Stato iniziale: 3 dischi sul primo paletto ------

q(0,4321,0,0) :- true.

%------ Sposta disco dal primo paletto sul secondo o sul terzo ------

m(I1,S1,S2,L3) :-  q(I,L1,L2,L3),
                   I1 = I+1, number(J), I < J, L1 > 0,
                   L1=10/S1, %div(L1,10,S1),
                   mod(L1,10,X),
                   Z = L2*10,
                   S2 = Z + X,
                   allowed(S1),
                   allowed(S2).

m(I1,S1,L2,S3) :-  q(I,L1,L2,L3),
                   I1 = I+1, number(J), I < J, L1 > 0,
                   L1=10/S1, %div(L1,10,S1),
                   mod(L1,10,X),
                   W = L3*10,
                   S3 = W + X,
                   allowed(S1),
                   allowed(S3).

%------ Sposta disco dal secondo paletto sul primo o sul terzo ------

m(I1,S1,S2,L3) :-  q(I,L1,L2,L3),
                   I1 = I+1, number(J), I < J, L2 > 0,
                   L2=10/S2, %div(L2,10,S2),
                   mod(L2,10,X),
                   Z = L1*10,
                   S1 = Z + X,
                   allowed(S1),
                   allowed(S2).

m(I1,L1,S2,S3) :-  q(I,L1,L2,L3),
                   I1 = I+1, number(J), I < J, L2 > 0,
                   L2=10/S2, %div(L2,10,S2),
                   mod(L2,10,X),
                   W = L3*10,
                   S3 = W + X,
                   allowed(S2),
                   allowed(S3).

%------ Sposta disco dal terzo paletto sul primo o sul secondo ------

m(I1,S1,L2,S3) :-  q(I,L1,L2,L3),
                   I1 = I+1, number(J), I < J, L3 > 0,
                   L3=10/S3, %div(L3,10,S3),
                   mod(L3,10,X),
                   Z = L1*10,
                   S1 = Z + X,
                   allowed(S1),
                   allowed(S3).

m(I1,L1,S2,S3) :-  q(I,L1,L2,L3),
                   I1 = I+1, number(J), I < J, L3 > 0,
                   L3=10/S3, %div(L3,10,S3),
                   mod(L3,10,X),
                   W = L2*10,
                   S2 = W + X,
                   allowed(S2),
                   allowed(S3).

q(I,A1,A2,A3) | noq(I,A1,A2,A3) :- m(I,A1,A2,A3).

% ----- the last digit must be smaller than the last but one -----

allowed(L) :- L<10. %#int(L), L<10.
allowed(L) :- L>10, mod(L,10,X), L=10/Y, mod(Y,10,Z), X < Z. %div(L,10,Y), mod(Y,10,Z), X < Z.

%------ Vincolo: Una configurazione ad ogni step ------

%:- q(I,L1,L2,L3), q(J,L1,L2,L3), I != J.
:- q(I,L1,L2,L3), q(I,M1,M2,M3), L1 != M1.
:- q(I,L1,L2,L3), q(I,M1,M2,M3), L2 != M2.
:- q(I,L1,L2,L3), q(I,M1,M2,M3), L3 != M3.
%:- m(I,L1,L2,L3), not have_q(I). 

%have_q(I) :- q(I,_,_,_).

% ------ Query: Tre dischi sul secondo paletto ---

query(X,Y,Z) :- number(J), q(J,X,Y,Z).



% div(4321,10,432).
% div(432,10,43).
% div(431,10,43).
% div(421,10,42).
% div(43,10,4).
% div(42,10,4).
% div(41,10,4).
% div(321,10,32).
% div(312,10,31).
% div(231,10,23).
% div(213,10,21).
% div(132,10,13).
% div(123,10,12).
%div(32,10,3).
%div(31,10,3).
% div(23,10,2).
%div(21,10,2).
% div(13,10,1).
% div(12,10,1).
% div(4,10,0).
% div(3,10,0).
% div(2,10,0).
% div(1,10,0).

mod(4321,10,1).
mod(432,10,2).
mod(431,10,1).
mod(421,10,1).
mod(321,10,1).
mod(43,10,3).
mod(42,10,2).
mod(41,10,1).
% mod(312,10,2).
% mod(231,10,1).
% mod(213,10,3).
% mod(132,10,2).
% mod(123,10,3).
mod(32,10,2).
mod(31,10,1).
% mod(23,10,3).
mod(21,10,1).
% mod(13,10,3).
% mod(12,10,2).
mod(4,10,4).
mod(3,10,3).
mod(2,10,2).
mod(1,10,1).

query(0,0,4321)?
"""
