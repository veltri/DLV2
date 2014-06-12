input = """
b(f(2)).
b("f"(3)).

a("f"(X)) :- b(X).
"""
output = """
b(f(2)).
b("f"(3)).

a("f"(X)) :- b(X).
"""
