input = """

a(X) :- #count{Z: t(Y,Z)} = X, q(Y).

t(1,1).
t(1,2).
t(1,3).
t(2,4).
q(1).

%out{ a(3). } 




"""
output = """

a(X) :- #count{Z: t(Y,Z)} = X, q(Y).

t(1,1).
t(1,2).
t(1,3).
t(2,4).
q(1).

%out{ a(3). } 




"""
