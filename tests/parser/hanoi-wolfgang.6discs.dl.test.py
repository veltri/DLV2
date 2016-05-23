input = """
true.
number_of_moves(63).

largest_disc(6).

%------ Initial state

move(0,654321,0,0) :- true.

% ------ Goal state

query(X,Y,Z) :- move(J,X,Y,Z).

query(0,0,654321)?

%#maxint=654321.

"""
output = """
true.
number_of_moves(63).

largest_disc(6).

%------ Initial state

move(0,654321,0,0) :- true.

% ------ Goal state

query(X,Y,Z) :- move(J,X,Y,Z).

query(0,0,654321)?

%#maxint=654321.

"""
