input = """
% We do not have any answer set here (independently from the query, but not
% dectectable by the grounding).

color(red,X) | color(green,X) | color(blue,X) :- node(X).

node("Cosenza").
node("Vienna").
node("Diamante").

redish :- color(red,"Vienna").
dark :- not color(red,"Vienna").

:- redish, not dark.
:- dark, not redish.

color(X,Y)?
"""
output = """
% We do not have any answer set here (independently from the query, but not
% dectectable by the grounding).

color(red,X) | color(green,X) | color(blue,X) :- node(X).

node("Cosenza").
node("Vienna").
node("Diamante").

redish :- color(red,"Vienna").
dark :- not color(red,"Vienna").

:- redish, not dark.
:- dark, not redish.

color(X,Y)?
"""
