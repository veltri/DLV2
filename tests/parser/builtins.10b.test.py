input = """
a("10"). a("3").
b(X,Y) :- a(X), a(Y), X > Y.

"""
output = """
a("10"). a("3").
b(X,Y) :- a(X), a(Y), X > Y.

"""
