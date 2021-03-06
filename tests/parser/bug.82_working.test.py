input = """
% Sent by Michael Fink 2005-06-20, current release computes wrong answer sets
% having weight 0 (also wrong).
%#maxint=200.
%%
% Guess depots for highway (at restaurant locations)
%%

mcDepot(H,K) | -mcDepot(H,K) :- mcBurger(H,K). 

%%
% Check required number of depots
%%

:- nDepots(H,N), not #count{K : mcDepot(H,K)} = N.

%%
% Optimize local distance per highway
%%

%:- loc_dist(H,I,D). [D:H]

%%
% Auxiliary predicates
%%

% For each highway, compute all distances between restaurants and depots
dist(H,K,K,0) :- mcBurger(H,K), mcDepot(H,K).
dist(H,I,J,D) :- mcBurger(H,I), mcDepot(H,J), I>J, D=I-J.
dist(H,I,J,D) :- mcBurger(H,I), mcDepot(H,J), J>I, D=J-I.

% For each highway and any restaurant, determine local distance (to next depot)
loc_dist(H,I,D) :- dist(H,I,J,D), #min{S : dist(H,I,K,S)} = D.



%%
% Input for Highway A1
%%

highway(1).
km(1,25).
nDepots(1,3).

%%
% Restaurants along A1
%%

mcBurger(1, 4).
mcBurger(1, 9).
mcBurger(1,12).
mcBurger(1,21).
mcBurger(1,24).

%%
% Just for Testing
%%

mcDepot(1,12).


"""
output = """
% Sent by Michael Fink 2005-06-20, current release computes wrong answer sets
% having weight 0 (also wrong).
%#maxint=200.
%%
% Guess depots for highway (at restaurant locations)
%%

mcDepot(H,K) | -mcDepot(H,K) :- mcBurger(H,K). 

%%
% Check required number of depots
%%

:- nDepots(H,N), not #count{K : mcDepot(H,K)} = N.

%%
% Optimize local distance per highway
%%

%:- loc_dist(H,I,D). [D:H]

%%
% Auxiliary predicates
%%

% For each highway, compute all distances between restaurants and depots
dist(H,K,K,0) :- mcBurger(H,K), mcDepot(H,K).
dist(H,I,J,D) :- mcBurger(H,I), mcDepot(H,J), I>J, D=I-J.
dist(H,I,J,D) :- mcBurger(H,I), mcDepot(H,J), J>I, D=J-I.

% For each highway and any restaurant, determine local distance (to next depot)
loc_dist(H,I,D) :- dist(H,I,J,D), #min{S : dist(H,I,K,S)} = D.



%%
% Input for Highway A1
%%

highway(1).
km(1,25).
nDepots(1,3).

%%
% Restaurants along A1
%%

mcBurger(1, 4).
mcBurger(1, 9).
mcBurger(1,12).
mcBurger(1,21).
mcBurger(1,24).

%%
% Just for Testing
%%

mcDepot(1,12).


"""
