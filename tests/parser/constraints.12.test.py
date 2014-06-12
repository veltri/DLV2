input = """
g(0).
i(0).

:- i(X), g(X).

"""
output = """
g(0).
i(0).

:- i(X), g(X).

"""
