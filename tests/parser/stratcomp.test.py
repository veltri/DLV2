input = """
% Strategic Companies
%
% As we want to produce X, Y or Z must be strategic.

 strategic(Y) | strategic(Z) :- produced_by(X,Y,Z).

% W is strategic, if it is controlled by strategic 
% companies X, Y, and Z  

 strategic(W) :- controlled_by(W,X,Y,Z), 
                 Strategic(X), Strategic(Y), Strategic(Z). 

% Handle special 0 symbol 

 :- strategic(0). 
 Strategic(X) :- strategic(X).
 Strategic(0) :- true. 
 true. 
"""
output = """
% Strategic Companies
%
% As we want to produce X, Y or Z must be strategic.

 strategic(Y) | strategic(Z) :- produced_by(X,Y,Z).

% W is strategic, if it is controlled by strategic 
% companies X, Y, and Z  

 strategic(W) :- controlled_by(W,X,Y,Z), 
                 Strategic(X), Strategic(Y), Strategic(Z). 

% Handle special 0 symbol 

 :- strategic(0). 
 Strategic(X) :- strategic(X).
 Strategic(0) :- true. 
 true. 
"""
