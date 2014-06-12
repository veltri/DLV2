input = """
bluePath( X, Y ) :- blue( X, Y ).
bluePath( X, Y ) :- blue( X, Z ), bluePath( Z, Y ).

monopoly( X, Y ) :- red( X, Y ), not bluePath( X, Y ).

red( 1, 2 ).
red( 2, 3 ).
blue( 1, 2 ).

"""
output = """
bluePath( X, Y ) :- blue( X, Y ).
bluePath( X, Y ) :- blue( X, Z ), bluePath( Z, Y ).

monopoly( X, Y ) :- red( X, Y ), not bluePath( X, Y ).

red( 1, 2 ).
red( 2, 3 ).
blue( 1, 2 ).

"""
