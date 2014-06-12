input = """
% Definition of the blocks involved in this problem instance

block(b0).
block(b1).
block(b2).

% sussman anomaly


% goal: 0/1/2    (i.e., b0 is on the table, b1 is on b0, and b2 is on b1)

% define the initial state

%  2
%  0  1
% ------

init(b1, table).
init(b2, b0).
init(b0, table).

% specify the goal state as a query

%  2
%  1
%  0
% ---

%on(b2, b1, #maxint), on(b1, b0, #maxint), on(b0, table, #maxint) ?
on(b2, b1) ?
"""
output = """
% Definition of the blocks involved in this problem instance

block(b0).
block(b1).
block(b2).

% sussman anomaly


% goal: 0/1/2    (i.e., b0 is on the table, b1 is on b0, and b2 is on b1)

% define the initial state

%  2
%  0  1
% ------

init(b1, table).
init(b2, b0).
init(b0, table).

% specify the goal state as a query

%  2
%  1
%  0
% ---

%on(b2, b1, #maxint), on(b1, b0, #maxint), on(b0, table, #maxint) ?
on(b2, b1) ?
"""
