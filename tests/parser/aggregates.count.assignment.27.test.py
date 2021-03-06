input = """
h(1). h(2). h(3).

p(1,1).
p(2,2).

q(1,1).
q(2,2).

r(1,1).
r(1,2).
r(1,3).
r(2,2).
r(3,3).

%a(S,T,Z,B) :- #count{A: not r(T,Z), h(A)} = B, #count{X: not r(T,X), h(X)} = Z, #count{F: not q(W,S),h(F)} = T, h(W), #count{G: h(G), not p(G,Y)} = S, h(Y).
a(S,T,Z,B) :- #count{A: r(T,Z), h(A)} = B, #count{X: r(T,X), h(X)} = Z, #count{F: q(W,S),h(F)} = T, h(W), #count{G: h(G), p(G,Y)} = S, h(Y).
"""
output = """
h(1). h(2). h(3).

p(1,1).
p(2,2).

q(1,1).
q(2,2).

r(1,1).
r(1,2).
r(1,3).
r(2,2).
r(3,3).

%a(S,T,Z,B) :- #count{A: not r(T,Z), h(A)} = B, #count{X: not r(T,X), h(X)} = Z, #count{F: not q(W,S),h(F)} = T, h(W), #count{G: h(G), not p(G,Y)} = S, h(Y).
a(S,T,Z,B) :- #count{A: r(T,Z), h(A)} = B, #count{X: r(T,X), h(X)} = Z, #count{F: q(W,S),h(F)} = T, h(W), #count{G: h(G), p(G,Y)} = S, h(Y).
"""
