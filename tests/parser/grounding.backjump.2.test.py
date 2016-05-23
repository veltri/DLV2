input = """
% By this example we can check
% a) the correcteness of the jumps-arrays
% b) the correctness of the use of indexLastSolution and
% c) how we eliminate the duplicates of the rule
%    ok | -ok
ok | -ok :- p(A,B), q(E,F), r(F,E), t(A), s(B,A).

p(1,2).
p(2,1).
p(3,1).
q(3,4).
r(4,3).
t(1).
s(1,2).
t(3).
s(1,3).
t(2).
"""
output = """
% By this example we can check
% a) the correcteness of the jumps-arrays
% b) the correctness of the use of indexLastSolution and
% c) how we eliminate the duplicates of the rule
%    ok | -ok
ok | -ok :- p(A,B), q(E,F), r(F,E), t(A), s(B,A).

p(1,2).
p(2,1).
p(3,1).
q(3,4).
r(4,3).
t(1).
s(1,2).
t(3).
s(1,3).
t(2).
"""
