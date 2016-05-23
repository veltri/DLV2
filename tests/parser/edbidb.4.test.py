input = """
g(1,1):- true. true.
% Some edges of an Input graph
g(1,2).
g(2,3).
g(3,4).
g(7,6).

% The graph is undirected for X > 6.
g(Y,X):- X>6, g(X,Y).

g(4,2).

% Transitive Closure
g(X,Y):- g(X,Z), g(Z,Y).

g(6,5).
g(3,1).
"""
output = """
g(1,1):- true. true.
% Some edges of an Input graph
g(1,2).
g(2,3).
g(3,4).
g(7,6).

% The graph is undirected for X > 6.
g(Y,X):- X>6, g(X,Y).

g(4,2).

% Transitive Closure
g(X,Y):- g(X,Z), g(Z,Y).

g(6,5).
g(3,1).
"""
