input = """
% This is a synthetic example documenting a bug in an early version of DLV's
% backjumping algorithm.

% The abstract computation tree looks as follows (choice order should be fixed
% by disabling heuristics with -OH-):
%
%          o
%       a / \ -a
%        /   \_..._
%       o          \
%    b / \ -b      {-a,-b,f}
%     /   \
%    o     o
% incons   incons based on a and b
% based
% only
% on b
%
% The backjumping algorithm wrongly determined that in the bottom left
% subtree both inconsistencies are based only on the choice of b and
% therefore stopped the entire search, missing the model on the right.

a | -a.
b | -b.

% taking b causes inconsistency
x :- b.
y :- b.
:- x,y.

% taking -b causes m1 to be MBT, but only with a
% taking -b unconditionally causes d and e to be false
:- -b, a, not m1.
:- -b, d.
:- -b, e.

% m1 (which is MBT in the interesting branch) will have no supporting rule
% but this will be determined only when propagating d and e's falsity
% the reasons are obviously the choice for b and the choice for a
m1 :- d.
m1 :- e.

% avoid d and e to be always false 
% and allow a model with f
e | f.
d | f. 

"""
output = """
% This is a synthetic example documenting a bug in an early version of DLV's
% backjumping algorithm.

% The abstract computation tree looks as follows (choice order should be fixed
% by disabling heuristics with -OH-):
%
%          o
%       a / \ -a
%        /   \_..._
%       o          \
%    b / \ -b      {-a,-b,f}
%     /   \
%    o     o
% incons   incons based on a and b
% based
% only
% on b
%
% The backjumping algorithm wrongly determined that in the bottom left
% subtree both inconsistencies are based only on the choice of b and
% therefore stopped the entire search, missing the model on the right.

a | -a.
b | -b.

% taking b causes inconsistency
x :- b.
y :- b.
:- x,y.

% taking -b causes m1 to be MBT, but only with a
% taking -b unconditionally causes d and e to be false
:- -b, a, not m1.
:- -b, d.
:- -b, e.

% m1 (which is MBT in the interesting branch) will have no supporting rule
% but this will be determined only when propagating d and e's falsity
% the reasons are obviously the choice for b and the choice for a
m1 :- d.
m1 :- e.

% avoid d and e to be always false 
% and allow a model with f
e | f.
d | f. 

"""
