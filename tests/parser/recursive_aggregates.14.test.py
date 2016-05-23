input = """
% Company Controls

cv(X,X,Y,S) :- owns_stock(X,Y,S).
cv(X,Z,Y,S) :- company(X),controls(X,Z),owns_stock(Z,Y,S).

controls(X,Y) :- 
    50 < #sum{S,Z : cv(X,Z,Y,S) }, company(X),company(Y).

company(a).
company(b).
company(c).

% from [Faber '04]
owns_stock(a,b,60). 
owns_stock(a,c,36). 
owns_stock(b,a,20). 
owns_stock(b,c,16). 
owns_stock(c,a,32). 

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

% from [Faber '04]
owns_stock(a,b,60). 
owns_stock(a,c,36). 
owns_stock(b,a,20). 
owns_stock(b,c,16). 
owns_stock(c,a,32). 

"""
