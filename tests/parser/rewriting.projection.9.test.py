input = """

a(X,Y) :- c(X,R,S), d(S,Y), not na(X,Y).
na(X,Y) :- c(X,R,S), d(S,Y), not a(X,Y).

c(z,r,a).
c(z,s,a).

d(a,y).

"""
output = """

a(X,Y) :- c(X,R,S), d(S,Y), not na(X,Y).
na(X,Y) :- c(X,R,S), d(S,Y), not a(X,Y).

c(z,r,a).
c(z,s,a).

d(a,y).

"""
