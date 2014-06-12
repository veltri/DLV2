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
% taking -b unconditionally causes d to be false
:- -b, a, not m1.
:- -b, d.

% the constraint is violated if m1 is MBT and d is false
% the reasons are obviously the choice for b and the choice for a
:- m1, not d.

% give m1 a chance to be true
% if not allow a model with f
m1 | f.

% avoid d to be always false
% and allow a model with f
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
% taking -b unconditionally causes d to be false
:- -b, a, not m1.
:- -b, d.

% the constraint is violated if m1 is MBT and d is false
% the reasons are obviously the choice for b and the choice for a
:- m1, not d.

% give m1 a chance to be true
% if not allow a model with f
m1 | f.

% avoid d to be always false
% and allow a model with f
d | f. 

"""
