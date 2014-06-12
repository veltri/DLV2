input = """
a(Z,P):-p(X), p(Y), #count{S:w(X,S)} = P, #count{R:r(R,Y)} = Z, 0<#count{T:s(T,Y)}<Z.

p(1).
p(2).
w(1,1).
w(2,1).
w(2,2).
r(1,1).
r(2,1).
r(0,2).
r(2,2).
r(3,2).
r(4,2).
s(1,1).
s(2,1).
s(2,1).
s(2,2).
"""
output = """
a(Z,P):-p(X), p(Y), #count{S:w(X,S)} = P, #count{R:r(R,Y)} = Z, 0<#count{T:s(T,Y)}<Z.

p(1).
p(2).
w(1,1).
w(2,1).
w(2,2).
r(1,1).
r(2,1).
r(0,2).
r(2,2).
r(3,2).
r(4,2).
s(1,1).
s(2,1).
s(2,1).
s(2,2).
"""
