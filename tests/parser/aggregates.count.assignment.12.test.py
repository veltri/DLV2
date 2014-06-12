input = """
r(W) :- W = #count{X: a(X,Y)}, c(Y).

a(1,2).
a(2,3).
c(1) | c(2).

"""
output = """
r(W) :- W = #count{X: a(X,Y)}, c(Y).

a(1,2).
a(2,3).
c(1) | c(2).

"""
