input = """
q(X) :- p(X).
p(f(X)) :- q(X).

q(f(a)).

"""
output = """
q(X) :- p(X).
p(f(X)) :- q(X).

q(f(a)).

"""
