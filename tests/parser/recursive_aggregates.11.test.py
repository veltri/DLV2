input = """
% Company Controls

cv(X,X,Y,S) :- owns_stock(X,Y,S).
cv(X,Z,Y,S) :- company(X),controls(X,Z),owns_stock(Z,Y,S).

controls(X,Y) :- 
    50 < #sum{S,Z : cv(X,Z,Y,S) }, company(X),company(Y).

company(a).
company(b).
company(c).

% from [Kemp and Stuckey '91]
owns_stock(a,b,60).
owns_stock(a,c,52).
owns_stock(b,a,20).
owns_stock(b,c,16).
"""
output = """
% Company Controls

cv(X,X,Y,S) :- owns_stock(X,Y,S).
cv(X,Z,Y,S) :- company(X),controls(X,Z),owns_stock(Z,Y,S).

controls(X,Y) :- 
    50 < #sum{S,Z : cv(X,Z,Y,S) }, company(X),company(Y).

company(a).
company(b).
company(c).

% from [Kemp and Stuckey '91]
owns_stock(a,b,60).
owns_stock(a,c,52).
owns_stock(b,a,20).
owns_stock(b,c,16).
"""
