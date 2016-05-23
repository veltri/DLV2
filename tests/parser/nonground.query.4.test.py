input = """
% This is most similar to nonground.query.3, just without the second
% constraint. We originally failed to process this correctly.

color(red,X) | color(green,X) | color(blue,X) :- node(X).

node("Cosenza").
node("Vienna").
node("Diamante").

redish :- color(red,"Vienna").
dark :- not color(red,"Vienna").

:- redish, not dark.
%:- dark, not redish.

color(X,Y)?
"""
output = """
% This is most similar to nonground.query.3, just without the second
% constraint. We originally failed to process this correctly.

color(red,X) | color(green,X) | color(blue,X) :- node(X).

node("Cosenza").
node("Vienna").
node("Diamante").

redish :- color(red,"Vienna").
dark :- not color(red,"Vienna").

:- redish, not dark.
%:- dark, not redish.

color(X,Y)?
"""
