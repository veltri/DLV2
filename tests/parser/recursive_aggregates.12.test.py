input = """
% Company Controls

cv(X,X,Y,S) :- owns_stock(X,Y,S).
cv(X,Z,Y,S) :- company(X),controls(X,Z),owns_stock(Z,Y,S).

controls(X,Y) :- 
    50 < #sum{S,Z : cv(X,Z,Y,S) }, company(X),company(Y).

company(a).
company(b).
company(c).

% from [Ross and Sagiv '92]
owns_stock(a,b,30).
owns_stock(a,c,30).
owns_stock(b,c,60).
owns_stock(c,b,60).
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

% from [Ross and Sagiv '92]
owns_stock(a,b,30).
owns_stock(a,c,30).
owns_stock(b,c,60).
owns_stock(c,b,60).
"""
