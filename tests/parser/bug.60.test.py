input = """
b :- not a.
a :- not b.

%:- m.
m | n.

"""
output = """
b :- not a.
a :- not b.

%:- m.
m | n.

"""
