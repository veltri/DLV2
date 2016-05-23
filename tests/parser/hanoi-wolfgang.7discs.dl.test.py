input = """
number_of_moves(127).

largest_disc(7).

%------ Initial state

move(0,7654321,0,0).

% ------ Goal state

query(X,Y,Z) :- move(J,X,Y,Z).

query(0,0,7654321)?

%#maxint=7654321.

"""
output = """
number_of_moves(127).

largest_disc(7).

%------ Initial state

move(0,7654321,0,0).

% ------ Goal state

query(X,Y,Z) :- move(J,X,Y,Z).

query(0,0,7654321)?

%#maxint=7654321.

"""
