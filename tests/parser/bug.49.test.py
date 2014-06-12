input = """
% This example is due to Thomas Eiter. It produces a segmentation fault in the
% DLV repository version of 2000-05-31.

% Generate a linear ordering compatible with 
% facts pr(ri,rj).

 pr(X,Y) | pr(Y,X) :- rule(X),rule(Y), X != Y. 

 pr(X,Z) :- pr(X,Y), pr(Y,Z). 

         :- pr(X,X). 

% Generate another ordering
%

 pr_one(X,Y) | pr_one(Y,X) :- rule(X),rule(Y), X != Y. 

 pr_one(X,Z) :- pr_one(X,Y), pr_one(Y,Z). 

         :- pr_one(X,X). 


% Minimize the difference between pr and pr_one

 %:- rule(X), rule(Y), pr(X,Y), not pr_one(X,Y). [1:1]



% Facts: three rules, one precedence per order.

  rule(r1).
  rule(r2).
  rule(r3).

  pr(r1,r2). 
  pr_one(r3,r1).


"""
output = """
% This example is due to Thomas Eiter. It produces a segmentation fault in the
% DLV repository version of 2000-05-31.

% Generate a linear ordering compatible with 
% facts pr(ri,rj).

 pr(X,Y) | pr(Y,X) :- rule(X),rule(Y), X != Y. 

 pr(X,Z) :- pr(X,Y), pr(Y,Z). 

         :- pr(X,X). 

% Generate another ordering
%

 pr_one(X,Y) | pr_one(Y,X) :- rule(X),rule(Y), X != Y. 

 pr_one(X,Z) :- pr_one(X,Y), pr_one(Y,Z). 

         :- pr_one(X,X). 


% Minimize the difference between pr and pr_one

 %:- rule(X), rule(Y), pr(X,Y), not pr_one(X,Y). [1:1]



% Facts: three rules, one precedence per order.

  rule(r1).
  rule(r2).
  rule(r3).

  pr(r1,r2). 
  pr_one(r3,r1).


"""
