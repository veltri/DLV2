input = """
a(X) | -a(X) :- . %#int(X).
:- not 0 <= #count{X:a(X)} <=1.
"""
output = """
a(X) | -a(X). %#int(X).
:- not 0 <= #count{X:a(X)} <=1.
"""
