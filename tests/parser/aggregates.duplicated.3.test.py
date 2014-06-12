input = """
mysum(X) :- #sum{P: c(P)} = X, dom(X).
%mytimes(X) :- #times{P: c(P)} = X, dom(X).

dom(0). dom(1).
c(X) | d(X) :- dom(X).

:- not c(0).
:- not c(1).
"""
output = """
mysum(X) :- #sum{P: c(P)} = X, dom(X).
%mytimes(X) :- #times{P: c(P)} = X, dom(X).

dom(0). dom(1).
c(X) | d(X) :- dom(X).

:- not c(0).
:- not c(1).
"""
