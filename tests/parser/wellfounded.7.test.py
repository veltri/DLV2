input = """
republican( nixon ).
quaker( nixon ).

pacifist( X ) :- quaker( X ), not -pacifist( X ).
hawk( X ) :- republican( X ), not -hawk( X ).

-pacifist( X ) :- hawk( X ).
-hawk( X ) :- pacifist( X ).

"""
output = """
republican( nixon ).
quaker( nixon ).

pacifist( X ) :- quaker( X ), not -pacifist( X ).
hawk( X ) :- republican( X ), not -hawk( X ).

-pacifist( X ) :- hawk( X ).
-hawk( X ) :- pacifist( X ).

"""
