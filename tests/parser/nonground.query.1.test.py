input = """
f(1). f(2). f(3). f(999).
true.

% These can be solved by the grounding...
F(X) :- f(X).
g(999) :- true.

% ...while these can not.
a | b.
g(X) :- f(X), b, X < 2.
g(X) :- f(X), b, X > 2.

% In the query we combine both, and also use a "guessed" atom.
F(Y) ? %, b, g(X)?
"""
output = """
f(1). f(2). f(3). f(999).
true.

% These can be solved by the grounding...
F(X) :- f(X).
g(999) :- true.

% ...while these can not.
a | b.
g(X) :- f(X), b, X < 2.
g(X) :- f(X), b, X > 2.

% In the query we combine both, and also use a "guessed" atom.
F(Y) ? %, b, g(X)?
"""
