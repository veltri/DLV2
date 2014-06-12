input = """
number_of_moves(31).

largest_disc(5).

%------ Initial state

move(0,54321,0,0).

% ------ Goal state

query(X,Y,Z) :- move(J,X,Y,Z).

query(0,0,54321)?

%#maxint=54321.

"""
output = """
number_of_moves(31).

largest_disc(5).

%------ Initial state

move(0,54321,0,0).

% ------ Goal state

query(X,Y,Z) :- move(J,X,Y,Z).

query(0,0,54321)?

%#maxint=54321.

"""
