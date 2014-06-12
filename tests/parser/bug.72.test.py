input = """
%#maxint=65535.
p :- a. %#int(X), a.
a | na.

"""
output = """
%#maxint=65535.
p :- a. %#int(X), a.
a | na.

"""
