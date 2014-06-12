input = """
h(1). h(2). h(3).

p(1,1).
p(2,2).

r(1,1).
r(1,2).
r(1,3).
r(2,2).
r(3,3).

%a(S,T,Z) :- #count{X: not r(T,X), h(X)} = Z, T=Y+S, #count{G: h(G), not p(G,Y)} = S, h(Y).
a(S,T,Z) :- #count{X: r(T,X), h(X)} = Z, T=Y+S, #count{G: h(G), p(G,Y)} = S, h(Y)."""
output = """
h(1). h(2). h(3).

p(1,1).
p(2,2).

r(1,1).
r(1,2).
r(1,3).
r(2,2).
r(3,3).

%a(S,T,Z) :- #count{X: not r(T,X), h(X)} = Z, T=Y+S, #count{G: h(G), not p(G,Y)} = S, h(Y).
a(S,T,Z) :- #count{X: r(T,X), h(X)} = Z, T=Y+S, #count{G: h(G), p(G,Y)} = S, h(Y)."""
