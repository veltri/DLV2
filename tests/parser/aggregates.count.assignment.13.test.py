input = """
r(W) :- W = #count{X: a(X,Y)}, c(Y).

a(1,2).
a(2,3).
c(1) :- not c(2).
c(2) :- not c(1).

"""
output = """
r(W) :- W = #count{X: a(X,Y)}, c(Y).

a(1,2).
a(2,3).
c(1) :- not c(2).
c(2) :- not c(1).

"""
