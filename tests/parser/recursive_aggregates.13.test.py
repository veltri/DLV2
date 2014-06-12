input = """
% Company Controls

cv(X,X,Y,S) :- owns_stock(X,Y,S).
cv(X,Z,Y,S) :- company(X),controls(X,Z),owns_stock(Z,Y,S).

controls(X,Y) :- 
    50 < #sum{S,Z : cv(X,Z,Y,S) }, company(X),company(Y).

company(a).
company(b).
company(c).

% from [Van Gelder '93]
owns_stock(a,b,40).
owns_stock(b,b,20).
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

% from [Van Gelder '93]
owns_stock(a,b,40).
owns_stock(b,b,20).
"""
