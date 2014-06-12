input = """
a(X) | -a(X) :- .%#int(X).
%b :- a(X).
b :- not 0 <= #count{X:a(X)} <= 0.
"""
output = """
a(X) | -a(X).%#int(X).
%b :- a(X).
b :- not 0 <= #count{X:a(X)} <= 0.
"""
