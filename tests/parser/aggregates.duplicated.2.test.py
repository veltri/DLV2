input = """
mymax(X) :- #max{P: c(P)} = X, dom(X).
mymin(X) :- #min{P: c(P)} = X, dom(X).

dom(0). dom(1).
c(X) | d(X) :- dom(X).

:- not c(0).
:- not c(1).
"""
output = """
mymax(X) :- #max{P: c(P)} = X, dom(X).
mymin(X) :- #min{P: c(P)} = X, dom(X).

dom(0). dom(1).
c(X) | d(X) :- dom(X).

:- not c(0).
:- not c(1).
"""
