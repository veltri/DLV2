input = """
i(0). i(1).
a(X) | -a(X) :- i(X).
ok :- 0 < #count{X:a(X)}< 2.
:- not ok.
"""
output = """
i(0). i(1).
a(X) | -a(X) :- i(X).
ok :- 0 < #count{X:a(X)}< 2.
:- not ok.
"""
