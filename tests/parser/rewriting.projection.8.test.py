input = """
a(X,Y) | b(X,Y) :- c(X,R,S), d(S,Y).

c(z,z,a).
c(z,r,a).
c(z,s,a).

d(a,y).

"""
output = """
a(X,Y) | b(X,Y) :- c(X,R,S), d(S,Y).

c(z,z,a).
c(z,r,a).
c(z,s,a).

d(a,y).

"""
