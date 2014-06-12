input = """
win( X ) :- move( X, Y ), not win( Y ).

move( a, d ).
move( b, c ).

"""
output = """
win( X ) :- move( X, Y ), not win( Y ).

move( a, d ).
move( b, c ).

"""
