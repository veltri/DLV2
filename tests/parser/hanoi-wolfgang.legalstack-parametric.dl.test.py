input = """
% Employ the notion of legal stacks, which carry information of the top
% element and the rest of the stack in addition to the entire stack itself.

% ------ all discs involved ------

disc(X) :- largest_disc(X).
disc(X) :- disc(Y), X != 0. %#succ(X,Y), X != 0.

% ------ legal non-empty stacks, their top element and the rest stack ------

legalstack_top_rest(D,D,0) :- disc(D).
legalstack_top_rest(S,T,B) :- legalstack_top_rest(B,T1,R1), disc(T), T < T1,
                              AUX = B * 10, S = AUX + T.

% ------ possible moves ------

% From stack one to stack two.

possible_move(I1,S1,S2,L3) :-  move(I,L1,L2,L3),
                               number_of_moves(J), I < J, %#succ(I,I1),
                               legalstack_top_rest(L1,X,S1),
                               legalstack_top_rest(S2,X,L2).

% From stack one to stack three.

possible_move(I1,S1,L2,S3) :-  move(I,L1,L2,L3),
                               number_of_moves(J), I < J, %#succ(I,I1),
                               legalstack_top_rest(L1,X,S1),
                               legalstack_top_rest(S3,X,L3).

% From stack two to stack one.

possible_move(I1,S1,S2,L3) :-  move(I,L1,L2,L3),
                               number_of_moves(J), I < J, %#succ(I,I1),
                               legalstack_top_rest(L2,X,S2),
                               legalstack_top_rest(S1,X,L1).

% From stack two to stack three.

possible_move(I1,L1,S2,S3) :-  move(I,L1,L2,L3),
                               number_of_moves(J), I < J, %#succ(I,I1),
                               legalstack_top_rest(L2,X,S2),
                               legalstack_top_rest(S3,X,L3).

% From stack three to stack one.

possible_move(I1,S1,L2,S3) :-  move(I,L1,L2,L3),
                               number_of_moves(J), I < J, %#succ(I,I1),
                               legalstack_top_rest(L3,X,S3),
                               legalstack_top_rest(S1,X,L1).

% From stack three to stack two.

possible_move(I1,L1,S2,S3) :-  move(I,L1,L2,L3),
                               number_of_moves(J), I < J, %#succ(I,I1),
                               legalstack_top_rest(L3,X,S3),
                               legalstack_top_rest(S2,X,L2).

%------ actual moves ------

% Choose from the possible moves.

move(I,A1,A2,A3) | nomove(I,A1,A2,A3) :- possible_move(I,A1,A2,A3).

%------ one configuration at each step ------

:- move(I,L1,L2,L3), move(I,M1,M2,M3), L1 != M1.
:- move(I,L1,L2,L3), move(I,M1,M2,M3), L2 != M2.
:- move(I,L1,L2,L3), move(I,M1,M2,M3), L3 != M3.

"""
output = """
% Employ the notion of legal stacks, which carry information of the top
% element and the rest of the stack in addition to the entire stack itself.

% ------ all discs involved ------

disc(X) :- largest_disc(X).
disc(X) :- disc(Y), X != 0. %#succ(X,Y), X != 0.

% ------ legal non-empty stacks, their top element and the rest stack ------

legalstack_top_rest(D,D,0) :- disc(D).
legalstack_top_rest(S,T,B) :- legalstack_top_rest(B,T1,R1), disc(T), T < T1,
                              AUX = B * 10, S = AUX + T.

% ------ possible moves ------

% From stack one to stack two.

possible_move(I1,S1,S2,L3) :-  move(I,L1,L2,L3),
                               number_of_moves(J), I < J, %#succ(I,I1),
                               legalstack_top_rest(L1,X,S1),
                               legalstack_top_rest(S2,X,L2).

% From stack one to stack three.

possible_move(I1,S1,L2,S3) :-  move(I,L1,L2,L3),
                               number_of_moves(J), I < J, %#succ(I,I1),
                               legalstack_top_rest(L1,X,S1),
                               legalstack_top_rest(S3,X,L3).

% From stack two to stack one.

possible_move(I1,S1,S2,L3) :-  move(I,L1,L2,L3),
                               number_of_moves(J), I < J, %#succ(I,I1),
                               legalstack_top_rest(L2,X,S2),
                               legalstack_top_rest(S1,X,L1).

% From stack two to stack three.

possible_move(I1,L1,S2,S3) :-  move(I,L1,L2,L3),
                               number_of_moves(J), I < J, %#succ(I,I1),
                               legalstack_top_rest(L2,X,S2),
                               legalstack_top_rest(S3,X,L3).

% From stack three to stack one.

possible_move(I1,S1,L2,S3) :-  move(I,L1,L2,L3),
                               number_of_moves(J), I < J, %#succ(I,I1),
                               legalstack_top_rest(L3,X,S3),
                               legalstack_top_rest(S1,X,L1).

% From stack three to stack two.

possible_move(I1,L1,S2,S3) :-  move(I,L1,L2,L3),
                               number_of_moves(J), I < J, %#succ(I,I1),
                               legalstack_top_rest(L3,X,S3),
                               legalstack_top_rest(S2,X,L2).

%------ actual moves ------

% Choose from the possible moves.

move(I,A1,A2,A3) | nomove(I,A1,A2,A3) :- possible_move(I,A1,A2,A3).

%------ one configuration at each step ------

:- move(I,L1,L2,L3), move(I,M1,M2,M3), L1 != M1.
:- move(I,L1,L2,L3), move(I,M1,M2,M3), L2 != M2.
:- move(I,L1,L2,L3), move(I,M1,M2,M3), L3 != M3.

"""
