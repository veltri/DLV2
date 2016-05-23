input = """
number_of_moves(15).

largest_disc(4).

%------ Initial state

move(0,4321,0,0).

% ------ Goal state

query(X,Y,Z) :- move(J,X,Y,Z).

query(0,0,4321)?

%#maxint=4321.
"""
output = """
number_of_moves(15).

largest_disc(4).

%------ Initial state

move(0,4321,0,0).

% ------ Goal state

query(X,Y,Z) :- move(J,X,Y,Z).

query(0,0,4321)?

%#maxint=4321.
"""
