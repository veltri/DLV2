input = """
ok(X) :- p(f(f(X))), q(f(X)).

q(X) :- p(X).

p(f(X)) :- t(X).

p(f(a)).
t(f(a)).

"""
output = """
ok(X) :- p(f(f(X))), q(f(X)).

q(X) :- p(X).

p(f(X)) :- t(X).

p(f(a)).
t(f(a)).

"""
