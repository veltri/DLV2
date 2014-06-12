input = """
r(W) :- W = #sum{X: a(X,Y)}, c(Y).

a(1,2).
a(2,2).
c(1) | c(2).

"""
output = """
r(W) :- W = #sum{X: a(X,Y)}, c(Y).

a(1,2).
a(2,2).
c(1) | c(2).

"""
