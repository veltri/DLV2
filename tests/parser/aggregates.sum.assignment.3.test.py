input = """

a(S,T,Z) :- #sum{X: r(T,X)} = Z, #sum{W: p(W,Y)} = S, #sum{K: q(K,S)} = T.

q(1,3).
q(2,4).

r(1,1).
r(1,2).
r(1,3).
r(2,2).
r(3,3).

p(1,1). 
p(2,2).
%{out a(3,1,6).
"""
output = """

a(S,T,Z) :- #sum{X: r(T,X)} = Z, #sum{W: p(W,Y)} = S, #sum{K: q(K,S)} = T.

q(1,3).
q(2,4).

r(1,1).
r(1,2).
r(1,3).
r(2,2).
r(3,3).

p(1,1). 
p(2,2).
%{out a(3,1,6).
"""
