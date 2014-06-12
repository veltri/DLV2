input = """
a(X) | -a(X).
ok :- 0 < #count{X:a(X)}< 2.
:- not ok.
"""
output = """
a(X) | -a(X).
ok :- 0 < #count{X:a(X)}< 2.
:- not ok.
"""
