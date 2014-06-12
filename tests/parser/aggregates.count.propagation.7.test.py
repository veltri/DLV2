input = """
c(1) | c(2).
a(X) :- c(X).
p(4).

ouch1 :- 0 < #count{V : a(V)} < 1.
ouch2(X) :- c(X), 1 < #count{Y:p(Y)}.
okay1(X) :- p(X), #count{Y:p(Y)} = 1.
okay2(X) :- c(X), #count{Y:p(Y)} = 1.
"""
output = """
c(1) | c(2).
a(X) :- c(X).
p(4).

ouch1 :- 0 < #count{V : a(V)} < 1.
ouch2(X) :- c(X), 1 < #count{Y:p(Y)}.
okay1(X) :- p(X), #count{Y:p(Y)} = 1.
okay2(X) :- c(X), #count{Y:p(Y)} = 1.
"""
