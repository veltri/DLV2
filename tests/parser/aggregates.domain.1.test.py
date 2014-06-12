input = """
% This testcase verifies that we properly handle aggregates over an
% undefined (or empty) predicate.

count(R)  :- R = #count{ X : f(X)}.
sum  (R)  :- R = #sum  { X : f(X)}.
%times(R)  :- R = #times{ X : f(X)}.
min(R)    :- R = #min  { X : f(X)}.
max(R)    :- R = #max  { X : f(X)}.

undefmin1 :-     #min{ X : f(X)} <= 3.
undefmin2 :-     #min{ X : f(X)} >= 3.
undefmin3 :- not #min{ X : f(X)} <= 3.
undefmin4 :- not #min{ X : f(X)} >= 3.

undefmax1 :-     #max{ X : f(X)} <= 3.
undefmax2 :-     #max{ X : f(X)} >= 3.
undefmax3 :- not #max{ X : f(X)} <= 3.
undefmax4 :- not #max{ X : f(X)} >= 3.
"""
output = """
% This testcase verifies that we properly handle aggregates over an
% undefined (or empty) predicate.

count(R)  :- R = #count{ X : f(X)}.
sum  (R)  :- R = #sum  { X : f(X)}.
%times(R)  :- R = #times{ X : f(X)}.
min(R)    :- R = #min  { X : f(X)}.
max(R)    :- R = #max  { X : f(X)}.

undefmin1 :-     #min{ X : f(X)} <= 3.
undefmin2 :-     #min{ X : f(X)} >= 3.
undefmin3 :- not #min{ X : f(X)} <= 3.
undefmin4 :- not #min{ X : f(X)} >= 3.

undefmax1 :-     #max{ X : f(X)} <= 3.
undefmax2 :-     #max{ X : f(X)} >= 3.
undefmax3 :- not #max{ X : f(X)} <= 3.
undefmax4 :- not #max{ X : f(X)} >= 3.
"""
