input = """


g(3,4).
g(4,1).

h(X,Y):- h(Y,X).

g(X,Y):- h(X,Z), g(Z,Y).

h(3,4).

g(5,2).


"""
output = """


g(3,4).
g(4,1).

h(X,Y):- h(Y,X).

g(X,Y):- h(X,Z), g(Z,Y).

h(3,4).

g(5,2).


"""
